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


#ifndef PHOTOMATCH_FLANN_MATCHER_H
#define PHOTOMATCH_FLANN_MATCHER_H

#include "photomatch/photomatch_global.h"
#include "photomatch/core/features/matcher.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT FlannMatcherProperties
  : public FlannMatcher
{

public:

  FlannMatcherProperties();
  ~FlannMatcherProperties() override;

// Match interface

public:

  void reset() override;
  QString name() const final;

// IFlannMatcher interface

public:

  Index index() const override;
  virtual void setIndex(Index index) override;

private:

  Index mIndex;
};

/*----------------------------------------------------------------*/

class PHOTOMATCH_EXPORT FlannMatcherImp
  : public FlannMatcherProperties,
    public DescriptorMatcher
{

public:

  FlannMatcherImp();
  explicit FlannMatcherImp(FlannMatcher::Index index);
  ~FlannMatcherImp() override = default;

private:

  void update();

// DescriptorMatcher interface

public:

  bool match(const cv::Mat &queryDescriptors,
             const cv::Mat &trainDescriptors,
             std::vector<cv::DMatch> &matches,
             const cv::Mat &mask = cv::Mat()) override;

  bool match(const cv::Mat &queryDescriptors,
             const cv::Mat &trainDescriptors,
             std::vector<std::vector<cv::DMatch>> &matches,
             const cv::Mat &mask = cv::Mat()) override;

// Match interface

public:

  void reset() override;

// IFlannMatcher interface

public:

  void setIndex(Index index) override;

protected:

  cv::Ptr<cv::FlannBasedMatcher> mFlannBasedMatcher;

};

} // namespace photomatch

#endif // PHOTOMATCH_FLANN_MATCHER_H
