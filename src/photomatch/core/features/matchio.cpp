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


#include "matchio.h"

#include <tidop/core/messages.h>

#include <QFileInfo>

#include <stdexcept>

namespace photomatch
{

MatchesReader::MatchesReader(const QString &fileName)
  : mFileName(fileName)
{

}

std::vector<cv::DMatch> MatchesReader::goodMatches() const
{
  return mGoodMatches;
}

std::vector<cv::DMatch> MatchesReader::wrongMatches() const
{
  return mWrongMatches;
}



/* ---------------------------------------------------------------------------------- */



MatchesWriter::MatchesWriter(const QString &fileName)
  : mFileName(fileName)
{

}

void MatchesWriter::setGoodMatches(const std::vector<cv::DMatch> &goodMatches)
{
  mGoodMatches = goodMatches;
}

void MatchesWriter::setWrongMatches(const std::vector<cv::DMatch> &wrongMatches)
{
  mWrongMatches = wrongMatches;
}



/* ---------------------------------------------------------------------------------- */


class MatchesReaderBinary
    : public MatchesReader
{

public:

  explicit MatchesReaderBinary(const QString &fileName);
  ~MatchesReaderBinary() override = default;

// MatchesReader interface

public:

  bool read() override;

private:

  void open();
  bool isOpen();
  void readHeader();
  void readMatches(std::vector<cv::DMatch> *matches);
  void readGoodMatches();
  void readWrongMatches();
  void close();

private:

  FILE *mFile;
  uint64_t mSizeGoodMatches{0};
  uint64_t mSizeWrongMatches{0};

};


MatchesReaderBinary::MatchesReaderBinary(const QString &fileName)
  : MatchesReader(fileName),
    mFile(nullptr)
{

}



bool MatchesReaderBinary::read()
{
  try {
    open();
    if (isOpen()) {
      readHeader();
      readGoodMatches();
      readWrongMatches();
      close();
    }
    return false;
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}

void MatchesReaderBinary::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *match_file = ba.data();
  mFile = std::fopen(match_file, "rb");
}

bool MatchesReaderBinary::isOpen()
{
  return mFile;
}

void MatchesReaderBinary::readHeader()
{
  char h[22];
  char extraHead[100];
  std::fread(h, sizeof(char), 22, mFile);
  std::fread(&mSizeGoodMatches, sizeof(uint64_t), 1, mFile);
  std::fread(&mSizeWrongMatches, sizeof(uint64_t), 1, mFile);
  std::fread(&extraHead, sizeof(char), 100, mFile);
}

void MatchesReaderBinary::readMatches(std::vector<cv::DMatch> *matches)
{
  for (auto &match : *matches) {
    std::fread(&match.queryIdx, sizeof(int32_t), 1, mFile);
    std::fread(&match.trainIdx, sizeof(int32_t), 1, mFile);
    std::fread(&match.imgIdx, sizeof(int32_t), 1, mFile);
    std::fread(&match.distance, sizeof(float), 1, mFile);
  }
}

void MatchesReaderBinary::readGoodMatches()
{
  mGoodMatches.resize(static_cast<size_t>(mSizeGoodMatches));
  readMatches(&mGoodMatches);
}

void MatchesReaderBinary::readWrongMatches()
{
  mWrongMatches.resize(static_cast<size_t>(mSizeWrongMatches));
  readMatches(&mWrongMatches);
}

void MatchesReaderBinary::close()
{
  std::fclose(mFile);
}



/* ---------------------------------------------------------------------------------- */


class MatchesReaderOpenCV
  : public MatchesReader
{

public:

  explicit MatchesReaderOpenCV(const QString &fileName);
  ~MatchesReaderOpenCV() override;

// MatchesReader interface

public:

  bool read() override;

private:

  void open();
  bool isOpen();
  void readGoodMatches();
  void readWrongMatches();
  void close();

private:

  cv::FileStorage *mFileStorage;
};


MatchesReaderOpenCV::MatchesReaderOpenCV(const QString &fileName)
  : MatchesReader(fileName),
    mFileStorage(nullptr)
{

}

MatchesReaderOpenCV::~MatchesReaderOpenCV()
{
  if (mFileStorage) {
    delete mFileStorage;
    mFileStorage = nullptr;
  }
}

bool MatchesReaderOpenCV::read()
{
  try {
    open();
    if (isOpen()) {
      readGoodMatches();
      readWrongMatches();
      close();
    }
    return false;
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}

void MatchesReaderOpenCV::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *match_file = ba.data();
  mFileStorage = new cv::FileStorage(match_file, cv::FileStorage::READ);
}

bool MatchesReaderOpenCV::isOpen()
{
  if (mFileStorage == nullptr) return false;
  return mFileStorage->isOpened();
}

void MatchesReaderOpenCV::readGoodMatches()
{
  mGoodMatches.resize(0);
  (*mFileStorage)["matches"] >> mGoodMatches;
}

void MatchesReaderOpenCV::readWrongMatches()
{
  mWrongMatches.resize(0);
  (*mFileStorage)["wrong_matches"] >> mWrongMatches;
}

void MatchesReaderOpenCV::close()
{
  if (mFileStorage)
    mFileStorage->release();
}



/* ---------------------------------------------------------------------------------- */

class MatchesWriterBinary
  : public MatchesWriter
{

public:

  explicit MatchesWriterBinary(const QString &fileName);
  ~MatchesWriterBinary() override = default;

// MatchesWriter interface

public:

  bool write() override;

private:

  void open();
  bool isOpen() const;
  void writeHeader() const;
  void writeGoodMatches() const;
  void writeWrongMatches() const;
  void writeMatches(const std::vector<cv::DMatch> &matches) const;
  void close();

private:

  FILE *mFile;

};

MatchesWriterBinary::MatchesWriterBinary(const QString &fileName)
  : MatchesWriter(fileName)
{
}

bool MatchesWriterBinary::write()
{
  try {
    open();
    if (isOpen()) {
      writeHeader();
      writeGoodMatches();
      writeWrongMatches();
      close();
    }
    return false;
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}

void MatchesWriterBinary::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *match_file = ba.data();
  mFile = std::fopen(match_file, "wb");
}

bool MatchesWriterBinary::isOpen() const
{
  return mFile;
}

void MatchesWriterBinary::writeHeader() const
{
  uint64_t size = mGoodMatches.size();
  uint64_t size_wm = mWrongMatches.size();
  std::fwrite("TIDOPLIB-Matching-#01", sizeof("TIDOPLIB-Matching-#01"), 1, mFile);
  std::fwrite(&size, sizeof(uint64_t), 1, mFile);
  std::fwrite(&size_wm, sizeof(uint64_t), 1, mFile);
  char extraHead[100]; // Reserva de espacio para futuros usos
  std::fwrite(&extraHead, sizeof(char), 100, mFile);
}

void MatchesWriterBinary::writeGoodMatches() const
{
  writeMatches(mGoodMatches);
}

void MatchesWriterBinary::writeWrongMatches() const
{
  writeMatches(mWrongMatches);
}

void MatchesWriterBinary::writeMatches(const std::vector<cv::DMatch> &matches) const
{
  for (size_t i = 0; i < matches.size(); i++) {
    std::fwrite(&matches[i].queryIdx, sizeof(int32_t), 1, mFile);
    std::fwrite(&matches[i].trainIdx, sizeof(int32_t), 1, mFile);
    std::fwrite(&matches[i].imgIdx, sizeof(int32_t), 1, mFile);
    std::fwrite(&matches[i].distance, sizeof(float), 1, mFile);
  }
}

void MatchesWriterBinary::close()
{
  std::fclose(mFile);
}


/* ---------------------------------------------------------------------------------- */



class MatchesWriterOpenCV
  : public MatchesWriter
{

public:

  explicit MatchesWriterOpenCV(const QString &fileName);
  ~MatchesWriterOpenCV() override;

// MatchesWriter interface

public:

  bool write() override;

private:

  void open();
  bool isOpen();
  void writeGoodMatches();
  void writeWrongMatches();
  void close();

private:

  int mMode;
  cv::FileStorage *mFileStorage;

};

MatchesWriterOpenCV::MatchesWriterOpenCV(const QString &fileName)
  : MatchesWriter(fileName),
    mFileStorage(nullptr)
{
  QString ext = QFileInfo(fileName).suffix();
  if (ext.compare("xml", Qt::CaseInsensitive) == 0) {
    mMode = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML;
  } else if (ext.compare("yml", Qt::CaseInsensitive) == 0) {
    mMode = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML;
  }
}

MatchesWriterOpenCV::~MatchesWriterOpenCV()
{
  if (mFileStorage) {
    delete mFileStorage;
    mFileStorage = nullptr;
  }
}

bool MatchesWriterOpenCV::write()
{
  try {
    open();
    if (isOpen()) {
      writeGoodMatches();
      writeWrongMatches();
      close();
    }
    return false;
  } catch (std::exception &e) {
    msgError(e.what());
    return true;
  }
}

void MatchesWriterOpenCV::open()
{
  QByteArray ba = mFileName.toLocal8Bit();
  const char *match_file = ba.data();
  mFileStorage = new cv::FileStorage(match_file, mMode);
}

bool MatchesWriterOpenCV::isOpen()
{
  if (mFileStorage == nullptr) return false;
  return mFileStorage->isOpened();
}

void MatchesWriterOpenCV::writeGoodMatches()
{
  if (mFileStorage)
    cv::write(*mFileStorage, "matches", mGoodMatches);
}

void MatchesWriterOpenCV::writeWrongMatches()
{
  if (mFileStorage)
    cv::write(*mFileStorage, "wrong_matches", mWrongMatches);
}

void MatchesWriterOpenCV::close()
{
  if (mFileStorage)
    mFileStorage->release();
}



/* ---------------------------------------------------------------------------------- */



std::unique_ptr<MatchesReader> MatchesReaderFactory::createReader(const QString &fileName)
{
  QString ext = QFileInfo(fileName).suffix();
  std::unique_ptr<MatchesReader> matches_reader;
  if (ext.compare("bin", Qt::CaseInsensitive) == 0) {
    matches_reader = std::make_unique<MatchesReaderBinary>(fileName);
  } else if (ext.compare("xml", Qt::CaseInsensitive) == 0){
    matches_reader = std::make_unique<MatchesReaderOpenCV>(fileName);
  } else if (ext.compare("yml", Qt::CaseInsensitive) == 0) {
    matches_reader = std::make_unique<MatchesReaderOpenCV>(fileName);
  } else {
    throw std::runtime_error("Invalid Matches Reader");
  }
  return matches_reader;
}


/* ---------------------------------------------------------------------------------- */


std::unique_ptr<MatchesWriter> MatchesWriterFactory::createWriter(const QString &fileName)
{
  QString ext = QFileInfo(fileName).suffix();
  std::unique_ptr<MatchesWriter> matches_writer;
  if (ext.compare("bin", Qt::CaseInsensitive) == 0) {
    matches_writer = std::make_unique<MatchesWriterBinary>(fileName);
  } else if (ext.compare("xml", Qt::CaseInsensitive) == 0){
    matches_writer = std::make_unique<MatchesWriterOpenCV>(fileName);
  } else if (ext.compare("yml", Qt::CaseInsensitive) == 0) {
    matches_writer = std::make_unique<MatchesWriterOpenCV>(fileName);
  } else {
    throw std::runtime_error("Invalid Writer Reader");
  }
  return matches_writer;
}





} // namespace photomatch
