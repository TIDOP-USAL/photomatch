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


#include "flann.h"

#include <tidop/core/messages.h>


namespace photomatch
{

FlannMatcherProperties::FlannMatcherProperties()
  : mIndex(FlannMatcherProperties::Index::kdtree)
{
}

FlannMatcherProperties::~FlannMatcherProperties()
{
}

void FlannMatcherProperties::reset()
{
  mIndex = FlannMatcherProperties::Index::kdtree;
}

QString FlannMatcherProperties::name() const
{
  return QString("Flann Based Matching");
}

FlannMatcher::Index FlannMatcherProperties::index() const
{
  return mIndex;
}

void FlannMatcherProperties::setIndex(FlannMatcher::Index index)
{
  mIndex = index;
}

/*----------------------------------------------------------------*/


FlannMatcherImp::FlannMatcherImp()
{
  update();
}

FlannMatcherImp::FlannMatcherImp(Index index)
{
  FlannMatcherProperties::setIndex(index);
  update();
}

void FlannMatcherImp::update()
{
  cv::Ptr<cv::flann::IndexParams> indexParams;
  if (FlannMatcherProperties::index() == FlannMatcherProperties::Index::kdtree){
    indexParams = cv::makePtr<cv::flann::KDTreeIndexParams>();
  } else if (FlannMatcherProperties::index() == FlannMatcherProperties::Index::lsh){
    indexParams = cv::makePtr<cv::flann::LshIndexParams>(12, 20, 2);
  }
  mFlannBasedMatcher = cv::Ptr<cv::FlannBasedMatcher>(new cv::FlannBasedMatcher(indexParams));
}

bool FlannMatcherImp::match(const cv::Mat &queryDescriptors,
                            const cv::Mat &trainDescriptors,
                            std::vector<cv::DMatch> &matches,
                            const cv::Mat &mask)
{
  try {
    mFlannBasedMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
  } catch (cv::Exception &e) {
    msgError("Flann Based Matcher error: %s", e.what());
    return true;
  }
  return false;
}

bool FlannMatcherImp::match(const cv::Mat &queryDescriptors,
                            const cv::Mat &trainDescriptors,
                            std::vector<std::vector<cv::DMatch>> &matches,
                            const cv::Mat &mask)
{
  try {
    mFlannBasedMatcher->knnMatch(queryDescriptors, trainDescriptors, matches, 2, mask);
  } catch (cv::Exception &e) {
    msgError("Flann Based Matcher error: %s", e.what());
    return true;
  }
  return false;
}

void FlannMatcherImp::reset()
{
  FlannMatcherProperties::reset();
  update();
}

void FlannMatcherImp::setIndex(FlannMatcher::Index index)
{
  FlannMatcherProperties::setIndex(index);
}

} // namespace photomatch
