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


#ifndef MATCHIO_H
#define MATCHIO_H

#include "photomatch/photomatch_global.h"

#include <memory>

#include <QString>

#include <opencv2/features2d.hpp>

namespace photomatch
{



class PHOTOMATCH_EXPORT MatchesReader
{

public:

  MatchesReader(const QString &fileName);
  virtual ~MatchesReader() = default;

  virtual bool read() = 0;

  std::vector<cv::DMatch> goodMatches() const;
  std::vector<cv::DMatch> wrongMatches() const;

protected:

  QString mFileName;
  std::vector<cv::DMatch> mGoodMatches;
  std::vector<cv::DMatch> mWrongMatches;
};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT MatchesWriter
{

public:

  MatchesWriter(const QString &fileName);
  virtual ~MatchesWriter() = default;

  virtual bool write() = 0;

  void setGoodMatches(const std::vector<cv::DMatch> &goodMatches);
  void setWrongMatches(const std::vector<cv::DMatch> &wrongMatches);

protected:

  QString mFileName;
  std::vector<cv::DMatch> mGoodMatches;
  std::vector<cv::DMatch> mWrongMatches;
};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT MatchesReaderFactory
{

private:

  MatchesReaderFactory() {}

public:

  static std::unique_ptr<MatchesReader> createReader(const QString &fileName);
};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT MatchesWriterFactory
{
public:

private:

  MatchesWriterFactory() {}

public:

  static std::unique_ptr<MatchesWriter> createWriter(const QString &fileName);
};





} // namespace photomatch


#endif // MATCHIO_H
