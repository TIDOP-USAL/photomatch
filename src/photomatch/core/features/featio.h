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


#ifndef PHOTOMATCH_FEATURES_IO_H
#define PHOTOMATCH_FEATURES_IO_H

#include "photomatch/photomatch_global.h"

#include <memory>

#include <QString>

#include <opencv2/features2d.hpp>

namespace photomatch
{

/*!
 * \brief FeaturesWriter class allows the writing of the detected features in different formats
 */
class PHOTOMATCH_EXPORT FeaturesWriter
{

public:

  FeaturesWriter(const QString &fileName);
  virtual ~FeaturesWriter() = default;

  virtual bool write() = 0;

  void setKeyPoints(const std::vector<cv::KeyPoint> &keyPoints);
  void setDescriptors(const cv::Mat &descriptors);

protected:

  QString mFileName;
  std::vector<cv::KeyPoint> mKeyPoints;
  cv::Mat mDescriptors;
};


/*----------------------------------------------------------------*/


/*!
 * \brief The FeaturesWriter class allows the reading of the different formats of features files
 */
class PHOTOMATCH_EXPORT FeaturesReader
{

public:

  FeaturesReader(const QString &fileName);
  virtual ~FeaturesReader() = default;

  virtual bool read() = 0;

  std::vector<cv::KeyPoint> keyPoints() const;
  cv::Mat descriptors() const;

protected:

  QString mFileName;
  std::vector<cv::KeyPoint> mKeyPoints;
  cv::Mat mDescriptors;
};



/*----------------------------------------------------------------*/



/*!
 * \brief Factory class to create different reading formats
 */
class PHOTOMATCH_EXPORT FeaturesReaderFactory
{

private:

  FeaturesReaderFactory() {}

public:

  static std::unique_ptr<FeaturesReader> createReader(const QString &fileName);
};

/*!
 * \brief Factory class to create different writing formats
 */
class PHOTOMATCH_EXPORT FeaturesWriterFactory
{
public:

private:

  FeaturesWriterFactory() {}

public:

  static std::unique_ptr<FeaturesWriter> createWriter(const QString &fileName);
};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT FeaturesIOHandler
{

public:

  FeaturesIOHandler();
  virtual ~FeaturesIOHandler() = default;

  bool read(const QString &file);
  bool write(const QString &file);
//  std::vector<cv::KeyPoint> keyPoints() const;
//  cv::Mat descriptors() const;
//  void setKeyPoints(const std::vector<cv::KeyPoint> &keyPoints);
//  void setDescriptors(const cv::Mat &descriptors);

protected:

  std::unique_ptr<FeaturesReader> mReader;
  std::unique_ptr<FeaturesWriter> mWriter;
};


} // namespace photomatch


#endif // PHOTOMATCH_FEATIO_H
