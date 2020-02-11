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


#include "MainWindowModel.h"

#include "photomatch/core/features/features.h"
#include "photomatch/core/features/matcher.h"
#include "photomatch/ui/ProjectModel.h"

#include <tidop/core/messages.h>

#include <easyexif/exif.h>

#include <opencv2/features2d.hpp>

#include <QStandardPaths>
#include <QDir>
#include <QImageReader>

namespace photomatch
{

MainWindowModel::MainWindowModel()
  : mPrjDefaultPath("")
{
  init();
}

QString MainWindowModel::defaultPath() const
{
  return mPrjDefaultPath;
}

std::list<std::pair<QString, QString>> MainWindowModel::exif(const QString &image) const
{
  std::list<std::pair<QString, QString>> exif;

  QByteArray ba = image.toLocal8Bit();
  const char *img_file = ba.constData();

  /// TODO: leer con GDAL
  QFileInfo file_info(image);
  if (file_info.suffix().compare("tif", Qt::CaseInsensitive) == 0){
    QImage qImage(image);
    if (qImage.isNull()) return exif;
    exif.push_back(std::make_pair(QString("Bits per sample"), QString::number(qImage.depth())));
    exif.push_back(std::make_pair(QString("Image width"), QString::number(qImage.width())));
    exif.push_back(std::make_pair(QString("Image height"), QString::number(qImage.height())));
    //exif[QString("Bits per sample")] = QString::number(qImage.depth());
    //exif[QString("Image width")] = QString::number(qImage.width());
    //exif[QString("Image height")] = QString::number(qImage.height());
  } else {
    // Read the JPEG file into a buffer
    FILE *fp = fopen(img_file, "rb");
    if (!fp) {
      msgError("Can't open file", img_file);
      return exif;
    }
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
      msgError("Can't read file", img_file);
      delete[] buf;
      return exif;
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code) {
      msgWarning("Error parsing EXIF: code %d\n", code);
      return exif;
    }
    exif.push_back(std::make_pair(QString("Camera make"), QString(result.Make.c_str())));
    exif.push_back(std::make_pair(QString("Camera model"), QString(result.Model.c_str())));
    exif.push_back(std::make_pair(QString("Software"), QString(result.Software.c_str())));
    exif.push_back(std::make_pair(QString("Bits per sample"), QString::number(result.BitsPerSample)));
    exif.push_back(std::make_pair(QString("Image width"), QString::number(result.ImageWidth)));
    exif.push_back(std::make_pair(QString("Image height"), QString::number(result.ImageHeight)));
    exif.push_back(std::make_pair(QString("Image description"), QString(result.ImageDescription.c_str())));
    exif.push_back(std::make_pair(QString("Image orientation"), QString::number(result.Orientation)));
    exif.push_back(std::make_pair(QString("Image copyright"), QString(result.Copyright.c_str())));
    exif.push_back(std::make_pair(QString("Image date/time"), QString(result.DateTime.c_str())));
    exif.push_back(std::make_pair(QString("Original date/time"), QString(result.DateTimeOriginal.c_str())));
    exif.push_back(std::make_pair(QString("Digitize date/time"), QString("1/%1").arg(static_cast<int>(1.0 / result.ExposureTime))));
    exif.push_back(std::make_pair(QString("Exposure time"), QString(result.DateTimeDigitized.c_str())));
    exif.push_back(std::make_pair(QString("F-stop"), QString("f/%1").arg(result.FNumber, 0, 'g', 1)));
    exif.push_back(std::make_pair(QString("ISO speed"), QString::number(result.ISOSpeedRatings)));
    exif.push_back(std::make_pair(QString("Subject distance"), QString::number(result.SubjectDistance).append(" m")));
    exif.push_back(std::make_pair(QString("Exposure bias"), QString::number(result.ExposureBiasValue).append(" EV")));
    exif.push_back(std::make_pair(QString("Lens focal length"), QString::number(result.FocalLength).append(" mm")));
    exif.push_back(std::make_pair(QString("35mm focal length"), QString::number(result.FocalLengthIn35mm).append(" mm")));
    exif.push_back(std::make_pair(QString("GPS Latitude"), QString("%1º%2'%3'' %4").arg(result.GeoLocation.LatComponents.degrees)
                                                            .arg(result.GeoLocation.LatComponents.minutes)
                                                            .arg(result.GeoLocation.LatComponents.seconds)
                                                            .arg(result.GeoLocation.LatComponents.direction)));
    exif.push_back(std::make_pair(QString("GPS Longitude"), QString("%1º%2'%3'' %4").arg(result.GeoLocation.LonComponents.degrees)
                                                             .arg(result.GeoLocation.LonComponents.minutes)
                                                             .arg(result.GeoLocation.LonComponents.seconds)
                                                             .arg(result.GeoLocation.LonComponents.direction)));
    exif.push_back(std::make_pair(QString("GPS Altitude"), QString::number(result.GeoLocation.Altitude).append(" m")));
    exif.push_back(std::make_pair(QString("GPS Precision (DOP)"), QString::number(result.GeoLocation.DOP)));
    exif.push_back(std::make_pair(QString("Lens min focal length"), QString::number(result.LensInfo.FocalLengthMin).append(" mm")));
    exif.push_back(std::make_pair(QString("Lens max focal length"), QString::number(result.LensInfo.FocalLengthMax).append(" mm")));
    exif.push_back(std::make_pair(QString("Lens f-stop min"), QString("f/%1").arg(result.LensInfo.FStopMin, 0, 'g', 1)));
    exif.push_back(std::make_pair(QString("Lens f-stop max"), QString("f/%1").arg(result.LensInfo.FStopMax, 0, 'g', 1)));
    exif.push_back(std::make_pair(QString("Lens make"), QString(result.LensInfo.Make.c_str())));
    exif.push_back(std::make_pair(QString("Lens model"), QString(result.LensInfo.Model.c_str())));
    exif.push_back(std::make_pair(QString("Focal plane XRes"), QString::number(result.LensInfo.FocalPlaneXResolution)));
    exif.push_back(std::make_pair(QString("Focal plane YRes"), QString::number(result.LensInfo.FocalPlaneYResolution)));
  }

  return exif;
}

std::vector<QPointF> MainWindowModel::loadKeyPointsCoordinates(const QString &file) const
{
  std::vector<QPointF> keyPoints;

  std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(file);
  featuresRead->read();
  std::vector<cv::KeyPoint> cvKeyPoints = featuresRead->keyPoints();

  if (cvKeyPoints.size() > 0){

    for (size_t i = 0; i < cvKeyPoints.size(); i++){
      QPointF pt(static_cast<qreal>(cvKeyPoints[i].pt.x),
                static_cast<qreal>(cvKeyPoints[i].pt.y));
      keyPoints.push_back(pt);
    }

  }

  return keyPoints;
}

std::vector<std::tuple<QPointF, double, double>> MainWindowModel::loadKeyPoints(const QString &file) const
{
  std::vector<std::tuple<QPointF, double, double>> keyPoints;

  std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(file);
  featuresRead->read();
  std::vector<cv::KeyPoint> cvKeyPoints = featuresRead->keyPoints();

  if (cvKeyPoints.size() > 0){

    for (size_t i = 0; i < cvKeyPoints.size(); i++){
      QPointF pt(static_cast<qreal>(cvKeyPoints[i].pt.x),
                static_cast<qreal>(cvKeyPoints[i].pt.y));
      keyPoints.push_back(std::make_tuple(pt, static_cast<double>(cvKeyPoints[i].size), static_cast<double>(cvKeyPoints[i].angle)));
    }

  }

  return keyPoints;
}

std::vector<std::pair<QPointF, QPointF> > MainWindowModel::loadMatches(const QString &fileMatches,
                                                                       const QString &fileKeyPoints1,
                                                                       const QString &fileKeyPoints2) const
{
  std::vector<std::pair<QPointF, QPointF>> r_matches;

  std::vector<cv::DMatch> match;
  matchesRead(fileMatches, &match);

  std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(fileKeyPoints1);
  featuresRead->read();
  std::vector<cv::KeyPoint> keyPoints1 = featuresRead->keyPoints();
  featuresRead = FeaturesReaderFactory::createReader(fileKeyPoints2);
  featuresRead->read();
  std::vector<cv::KeyPoint> keyPoints2 = featuresRead->keyPoints();

  /// Un tanto artificioso.... Revisar
  QString nameMatchesFile = QFileInfo(fileMatches).baseName();
  QString nameKeyPoints1File = QFileInfo(fileKeyPoints1).baseName();
  int idx = nameMatchesFile.indexOf(nameKeyPoints1File);
  for (size_t i = 0; i < match.size(); i++){
    size_t query_id = (idx == 0) ? static_cast<size_t>(match[i].queryIdx) : static_cast<size_t>(match[i].trainIdx);
    size_t train_id = (idx == 0) ? static_cast<size_t>(match[i].trainIdx) : static_cast<size_t>(match[i].queryIdx);
    QPointF pt_query(static_cast<double>(keyPoints1[query_id].pt.x),
                     static_cast<double>(keyPoints1[query_id].pt.y));
    QPointF pt_train(static_cast<double>(keyPoints2[train_id].pt.x),
                     static_cast<double>(keyPoints2[train_id].pt.y));

    r_matches.push_back(std::make_pair(pt_query, pt_train));
  }

  return r_matches;
}

void MainWindowModel::init()
{
  mPrjDefaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
  mPrjDefaultPath.append("/PhotoMatch/Projects");

  //TL_TODO("Solución provisional para cargar el idioma activo")
  //OptionsModel options;

  QDir dir(mPrjDefaultPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
}

} // namespace photomatch



