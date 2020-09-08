/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "featio.h"

#include <tidop/core/messages.h>
#include <tidop/core/exception.h>

#include <QFileInfo>

#include <stdexcept>

namespace photomatch
{

FeaturesWriter::FeaturesWriter(const QString &fileName)
  : mFileName(fileName)
{

}

void FeaturesWriter::setKeyPoints(const std::vector<cv::KeyPoint> &keyPoints)
{
  mKeyPoints = keyPoints;
}

void FeaturesWriter::setDescriptors(const cv::Mat &descriptors)
{
  mDescriptors = descriptors;
}



/* ---------------------------------------------------------------------------------- */



FeaturesReader::FeaturesReader(const QString &fileName)
  : mFileName(fileName)
{

}

std::vector<cv::KeyPoint> FeaturesReader::keyPoints() const
{
  return mKeyPoints;
}

cv::Mat FeaturesReader::descriptors() const
{
  return mDescriptors;
}




/* ---------------------------------------------------------------------------------- */




class FeaturesReaderBinary
    : public FeaturesReader
{

public:

  explicit FeaturesReaderBinary(const QString &fileName);
  ~FeaturesReaderBinary() override = default;

// FeaturesReader interface

public:

  bool read() override;

private:

  void open();
  bool isOpen();
  void readHeader();
  void readBody();
  void readKeypoints();
  void readDescriptors();
  void close();

private:

  FILE *mFile;
  int32_t mSize{0};
  int32_t mRows{0};
  int32_t mCols{0};
  int32_t mType{0};

};

FeaturesReaderBinary::FeaturesReaderBinary(const QString &fileName)
  : FeaturesReader(fileName),
    mFile(nullptr)
{

}

bool FeaturesReaderBinary::read()
{
  try {
    open();
    if (isOpen()) {
      readHeader();
      readBody();
      close();
    }
    return false;
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}

void FeaturesReaderBinary::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *feat_file = ba.data();
  mFile = std::fopen(feat_file, "rb");
}

bool FeaturesReaderBinary::isOpen()
{
  return mFile;
}

void FeaturesReaderBinary::readHeader()
{
  char h[24];
  char extraHead[200];
  std::fread(h, sizeof(char), 24, mFile);
  std::fread(&mSize, sizeof(int32_t), 1, mFile);
  std::fread(&mRows, sizeof(int32_t), 1, mFile);
  std::fread(&mCols, sizeof(int32_t), 1, mFile);
  std::fread(&mType, sizeof(int32_t), 1, mFile);
  std::fread(&extraHead, sizeof(char), 200, mFile);
}

void FeaturesReaderBinary::readBody()
{
  readKeypoints();
  readDescriptors();
}

void FeaturesReaderBinary::readKeypoints()
{
  mKeyPoints.resize(static_cast<size_t>(mSize));
  for (auto &keypoint : mKeyPoints) {
    std::fread(&keypoint.pt.x, sizeof(float), 1, mFile);
    std::fread(&keypoint.pt.y, sizeof(float), 1, mFile);
    std::fread(&keypoint.size, sizeof(float), 1, mFile);
    std::fread(&keypoint.angle, sizeof(float), 1, mFile);
    std::fread(&keypoint.response, sizeof(float), 1, mFile);
    std::fread(&keypoint.octave, sizeof(float), 1, mFile);
    std::fread(&keypoint.class_id, sizeof(float), 1, mFile);
  }
}

void FeaturesReaderBinary::readDescriptors()
{
  cv::Mat aux(static_cast<int>(mRows), static_cast<int>(mCols), mType);
  std::fread(aux.data, sizeof(float), static_cast<size_t>(mRows*mCols), mFile);
  aux.copyTo(mDescriptors);
  aux.release();
}

void FeaturesReaderBinary::close()
{
  std::fclose(mFile);
}


/* ---------------------------------------------------------------------------------- */




class FeaturesWriterBinary
    : public FeaturesWriter
{

public:

  explicit FeaturesWriterBinary(const QString &fileName);
  ~FeaturesWriterBinary() override = default;

  // FeaturesWriter interface

public:

  bool write() override;

private:

  void open();
  bool isOpen();
  void writeHeader();
  void writeBody();
  void close();

private:

  FILE *mFile;
};


FeaturesWriterBinary::FeaturesWriterBinary(const QString &fileName)
  : FeaturesWriter(fileName),
    mFile(nullptr)
{

}

bool FeaturesWriterBinary::write()
{
  try {
    open();
    if (isOpen()) {
      writeHeader();
      writeBody();
      close();
    }
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
  return false;

}

void FeaturesWriterBinary::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *feat_file = ba.data();
  mFile = std::fopen(feat_file, "rb");
}

bool FeaturesWriterBinary::isOpen()
{
  return mFile;
}

void FeaturesWriterBinary::writeHeader()
{
  int32_t size = static_cast<int32_t>(mKeyPoints.size());
  int32_t rows = static_cast<int32_t>(mDescriptors.rows);
  int32_t cols = static_cast<int32_t>(mDescriptors.cols);
  int32_t type = mDescriptors.type();
  std::fwrite("TIDOPLIB-Features2D-#01", sizeof("TIDOPLIB-Features2D-#01"), 1, mFile);
  std::fwrite(&size, sizeof(int32_t), 1, mFile);
  std::fwrite(&rows, sizeof(int32_t), 1, mFile);
  std::fwrite(&cols, sizeof(int32_t), 1, mFile);
  std::fwrite(&type, sizeof(int32_t), 1, mFile);
  char extraHead[200]; // Reserva de espacio para futuros usos
  std::fwrite(&extraHead, sizeof(char), 200, mFile);
}

void FeaturesWriterBinary::writeBody()
{
  for (auto &keyPoint : mKeyPoints) {
    std::fwrite(&keyPoint.pt.x, sizeof(float), 1, mFile);
    std::fwrite(&keyPoint.pt.y, sizeof(float), 1, mFile);
    std::fwrite(&keyPoint.size, sizeof(float), 1, mFile);
    std::fwrite(&keyPoint.angle, sizeof(float), 1, mFile);
    std::fwrite(&keyPoint.response, sizeof(float), 1, mFile);
    std::fwrite(&keyPoint.octave, sizeof(float), 1, mFile);
    std::fwrite(&keyPoint.class_id, sizeof(float), 1, mFile);
  }
  int32_t rows = static_cast<int32_t>(mDescriptors.rows);
  int32_t cols = static_cast<int32_t>(mDescriptors.cols);
  std::fwrite(mDescriptors.data, sizeof(float), static_cast<size_t>(rows*cols), mFile);
}

void FeaturesWriterBinary::close()
{
  std::fclose(mFile);
}

/* ---------------------------------------------------------------------------------- */



class FeaturesReaderOpenCV
    : public FeaturesReader
{

public:

  explicit FeaturesReaderOpenCV(const QString &fileName);
  ~FeaturesReaderOpenCV() override;

  // FeaturesReader interface

public:

  bool read() override;

private:

  void open();
  bool isOpen();
  void readkeypoints();
  void readDescriptor();
  void close();

private:

  cv::FileStorage *mFileStorage;
};

FeaturesReaderOpenCV::FeaturesReaderOpenCV(const QString &fileName)
  : FeaturesReader(fileName),
    mFileStorage(nullptr)
{

}

FeaturesReaderOpenCV::~FeaturesReaderOpenCV()
{
  if (mFileStorage) {
    delete mFileStorage;
    mFileStorage = nullptr;
  }
}

bool FeaturesReaderOpenCV::read()
{
  try {
    open();
    if (isOpen()) {
      readkeypoints();
      readDescriptor();
      close();
    }
    return false;
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}

void FeaturesReaderOpenCV::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *feat_file = ba.data();
  mFileStorage = new cv::FileStorage(feat_file, cv::FileStorage::READ);
}

bool FeaturesReaderOpenCV::isOpen()
{
  if (mFileStorage == nullptr) return false;
  return mFileStorage->isOpened();
}

void FeaturesReaderOpenCV::readkeypoints()
{
  if (mFileStorage) {
    mKeyPoints.resize(0);
    (*mFileStorage)["keypoints"] >> mKeyPoints;
  }
}

void FeaturesReaderOpenCV::readDescriptor()
{
  if (mFileStorage) {
    mDescriptors.resize(0);
    (*mFileStorage)["descriptors"] >> mDescriptors;
  }
}

void FeaturesReaderOpenCV::close()
{
  if (mFileStorage)
    mFileStorage->release();
}



/* ---------------------------------------------------------------------------------- */



class FeaturesWriterOpenCV
    : public FeaturesWriter
{

public:

  explicit FeaturesWriterOpenCV(const QString &fileName);
  ~FeaturesWriterOpenCV() override = default;

// FeaturesWriter interface

public:

  bool write() override;

private:

  void open();
  bool isOpen();
  void writeKeypoints();
  void writeDescriptors();
  void close();

private:

  int mMode;
  cv::FileStorage mFileStorage;
};


FeaturesWriterOpenCV::FeaturesWriterOpenCV(const QString &fileName)
  : FeaturesWriter(fileName)
{
  QString ext = QFileInfo(fileName).suffix();
  if (ext.compare("xml", Qt::CaseInsensitive) == 0) {
    mMode = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML;
  } else if (ext.compare("yml", Qt::CaseInsensitive) == 0) {
    mMode = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML;
  }
}

bool FeaturesWriterOpenCV::write()
{
  try {
    open();
    if (isOpen()){
      writeKeypoints();
      writeDescriptors();
      close();
    }
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
  return false;
}

void FeaturesWriterOpenCV::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *feat_file = ba.data();
  mFileStorage = cv::FileStorage(feat_file, mMode);
}

bool FeaturesWriterOpenCV::isOpen()
{
  return mFileStorage.isOpened();
}

void FeaturesWriterOpenCV::writeKeypoints()
{
  if (!mKeyPoints.empty()) cv::write(mFileStorage, "keypoints", mKeyPoints);
}

void FeaturesWriterOpenCV::writeDescriptors()
{
  if (!mDescriptors.empty()) cv::write(mFileStorage, "descriptors", mDescriptors);
}

void FeaturesWriterOpenCV::close()
{
  mFileStorage.release();
}



/* ---------------------------------------------------------------------------------- */




class FeaturesReaderTxt
  : public FeaturesReader
{

public:

  explicit FeaturesReaderTxt(const QString &fileName);
  ~FeaturesReaderTxt() override = default;

// FeaturesReader interface

public:

  bool read() override;

private:

  void open();
  bool isOpen();
  void readHeader();
  void readBody();
  void close();

private:

  std::ifstream ifs;
  int mType{0};
  int mSize{0};
  int mCols{0};
};

FeaturesReaderTxt::FeaturesReaderTxt(const QString &fileName)
  : FeaturesReader(fileName)
{

}

bool FeaturesReaderTxt::read()
{
  try {
    open();
    if (isOpen()) {
      readHeader();
      readBody();
      close();
    }
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
  return false;
}

void FeaturesReaderTxt::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *feat_file = ba.data();
  ifs = std::ifstream(feat_file);
}

bool FeaturesReaderTxt::isOpen()
{
  return ifs.is_open();
}

void FeaturesReaderTxt::readHeader()
{
  std::string line;
  std::getline(ifs, line);
  std::istringstream stream(line);
  stream >> mType >> mSize >> mCols;
}

void FeaturesReaderTxt::readBody()
{
  mKeyPoints.resize(static_cast<size_t>(mSize));
  mDescriptors = cv::Mat(mSize, mCols, mType);

  int r = 0;
  std::string line;
  while (std::getline(ifs, line)) {

    QStringList list = QString(line.c_str()).split(" ");
    mKeyPoints[static_cast<size_t>(r)].pt.x = list[0].toFloat();
    mKeyPoints[static_cast<size_t>(r)].pt.y = list[1].toFloat();
    mKeyPoints[static_cast<size_t>(r)].size = list[2].toFloat();
    mKeyPoints[static_cast<size_t>(r)].angle = list[3].toFloat();

    for (int c = 0; c < mCols; c++) {
      switch (mType) {
      case CV_8U:
        mDescriptors.at<uchar>(r,c) = static_cast<uchar>(list[c+4].toInt());
        break;
      case CV_8S:
        mDescriptors.at<schar>(r,c) = static_cast<schar>(list[c+4].toInt());
        break;
      case CV_16U:
        mDescriptors.at<ushort>(r,c) = static_cast<ushort>(list[c+4].toInt());
        break;
      case CV_16S:
        mDescriptors.at<short>(r,c) = static_cast<short>(list[c+4].toInt());
        break;
      case CV_32S:
        mDescriptors.at<int>(r,c) = list[c+4].toInt();
        break;
      case CV_32F:
        mDescriptors.at<float>(r,c) = list[c+4].toFloat();
        break;
      case CV_64F:
        mDescriptors.at<double>(r,c) = list[c+4].toDouble();
        break;
      default:
        break;
      }
    }
    r++;
  }
}

void FeaturesReaderTxt::close()
{
  ifs.close();
}


/* ---------------------------------------------------------------------------------- */



class FeaturesWriterTxt
    : public FeaturesWriter
{

public:

  explicit FeaturesWriterTxt(const QString &fileName);
  ~FeaturesWriterTxt() override = default;

  // FeaturesWriter interface

public:

  bool write() override
  {
    try {
      open();
      if (isOpen()){
        writeHeader();
        writeBody();
        close();
      }
    } catch (std::exception &e) {
      msgError(e.what());
      return true;
    }
    return false;
  }

private:

  void open();
  bool isOpen();
  void writeHeader();
  void writeBody();
  void close();

private:

  std::ofstream ofs;

};

FeaturesWriterTxt::FeaturesWriterTxt(const QString &fileName)
  : FeaturesWriter(fileName)
{

}

void FeaturesWriterTxt::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *feat_file = ba.data();
  ofs = std::ofstream(feat_file, std::ofstream::trunc);
}

bool FeaturesWriterTxt::isOpen()
{
  return ofs.is_open();
}

void FeaturesWriterTxt::writeHeader()
{
  ofs << mKeyPoints.size() << " " 
      <<  mDescriptors.cols << " " 
      << mDescriptors.type() << std::endl;
}

void FeaturesWriterTxt::writeBody()
{
  int size = static_cast<int>(mKeyPoints.size());
  int type = mDescriptors.type();

  for (int r = 0; r < size; r++) {
    cv::KeyPoint kp = mKeyPoints[static_cast<size_t>(r)];
    ofs << kp.pt.x << " " << kp.pt.y << " " << kp.size << " " << kp.angle;
    for (int c = 0; c < mDescriptors.cols; c++) {

      switch (type) {
        case CV_8U:
          ofs << " " << static_cast<int>(mDescriptors.at<uchar>(r,c));
          break;
        case CV_8S:
          ofs << " "  << static_cast<int>(mDescriptors.at<schar>(r,c));
          break;
        case CV_16U:
          ofs << " "  << static_cast<int>(mDescriptors.at<ushort>(r,c));
          break;
        case CV_16S:
          ofs << " "  << static_cast<int>(mDescriptors.at<short>(r,c));
          break;
        case CV_32S:
          ofs << " "  << mDescriptors.at<int>(r,c);
          break;
        case CV_32F:
          ofs << " "  << mDescriptors.at<float>(r,c);
          break;
        case CV_64F:
          ofs << " "  << mDescriptors.at<double>(r,c);
          break;
        default:
          ofs << " "  << -1;
          break;
      }
    }
    ofs << std::endl;
  }
}

void FeaturesWriterTxt::close()
{
  ofs.close();
}



/* ---------------------------------------------------------------------------------- */



std::unique_ptr<FeaturesReader> FeaturesReaderFactory::createReader(const QString &fileName)
{
  QString ext = QFileInfo(fileName).suffix();
  std::unique_ptr<FeaturesReader> features_reader;
  if (ext.compare("bin", Qt::CaseInsensitive) == 0) {
    features_reader = std::make_unique<FeaturesReaderBinary>(fileName);
  } else if (ext.compare("xml", Qt::CaseInsensitive) == 0) {
    features_reader = std::make_unique<FeaturesReaderOpenCV>(fileName);
  } else if (ext.compare("yml", Qt::CaseInsensitive) == 0) {
    features_reader = std::make_unique<FeaturesReaderOpenCV>(fileName);
  } else if (ext.compare("txt", Qt::CaseInsensitive) == 0) {
    features_reader = std::make_unique<FeaturesReaderTxt>(fileName);
  } else {
    throw TL_ERROR("Invalid Features Reader");
  }
  return features_reader;
}



/* ---------------------------------------------------------------------------------- */



std::unique_ptr<FeaturesWriter> FeaturesWriterFactory::createWriter(const QString &fileName)
{
  QString ext = QFileInfo(fileName).suffix();
  std::unique_ptr<FeaturesWriter> features_writer;
  if (ext.compare("bin", Qt::CaseInsensitive) == 0) {
    features_writer = std::make_unique<FeaturesWriterBinary>(fileName);
  } else if (ext.compare("txt", Qt::CaseInsensitive) == 0) {
    features_writer = std::make_unique<FeaturesWriterTxt>(fileName);
  } else if (ext.compare("xml", Qt::CaseInsensitive) == 0) {
    features_writer = std::make_unique<FeaturesWriterOpenCV>(fileName);
  } else if (ext.compare("yml", Qt::CaseInsensitive) == 0) {
    features_writer = std::make_unique<FeaturesWriterOpenCV>(fileName);
  } else {
    throw TL_ERROR("Invalid Features Writer");
  }
  return features_writer;
}



/* ---------------------------------------------------------------------------------- */



FeaturesIOHandler::FeaturesIOHandler()
{
}

bool FeaturesIOHandler::read(const QString &file)
{
  try {
    mReader = FeaturesReaderFactory::createReader(file);
    return mReader->read();
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}

bool FeaturesIOHandler::write(const QString &file)
{
  try {
    mWriter = FeaturesWriterFactory::createWriter(file);
    return mWriter->write();
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}


} // namespace photomatch

