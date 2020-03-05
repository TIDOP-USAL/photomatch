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


#include "keypointsfilter.h"

#include <tidop/core/messages.h>

namespace photomatch
{


KeyPointsFilterNBestProperties::KeyPointsFilterNBestProperties()
  : KeyPointsFilter(KeyPointsFilter::Type::n_best),
    mPointsNumber(5000)
{
}

int KeyPointsFilterNBestProperties::nPoints() const
{
  return mPointsNumber;
}

void KeyPointsFilterNBestProperties::setNPoints(int nPoints)
{
  mPointsNumber = nPoints;
}

void KeyPointsFilterNBestProperties::reset()
{
  mPointsNumber = 5000;
}



/*----------------------------------------------------------------*/



KeyPointsFilterNBest::KeyPointsFilterNBest()
{
}

KeyPointsFilterNBest::KeyPointsFilterNBest(int nPoints)
{
  this->setNPoints(nPoints);
}

void KeyPointsFilterNBest::setNPoints(int nPoints)
{
  KeyPointsFilterNBestProperties::setNPoints(nPoints);
}

bool KeyPointsFilterNBest::filter(const std::vector<cv::KeyPoint> &keypoints, std::vector<cv::KeyPoint> &filteredKeypoints)
{
  try {

    filteredKeypoints = keypoints;
    if (filteredKeypoints.size() <= static_cast<size_t>(KeyPointsFilterNBestProperties::nPoints()))
      return false;

    cv::KeyPointsFilter::retainBest(filteredKeypoints, KeyPointsFilterNBestProperties::nPoints());
    if (filteredKeypoints.size() != static_cast<size_t>(KeyPointsFilterNBestProperties::nPoints())){
      /// Los keypoints no tienen 'response'. Por ahora...
      filteredKeypoints.resize(static_cast<size_t>(KeyPointsFilterNBestProperties::nPoints()));
    }
    msgInfo("Filtered retaining %i best keypoints", KeyPointsFilterNBestProperties::nPoints());
    return false;
  } catch (cv::Exception &e) {
    msgError("Filtered keypoints error: %s", e.what());
    return true;
  }
}

void KeyPointsFilterNBest::reset()
{
  KeyPointsFilterNBestProperties::reset();
}


/*----------------------------------------------------------------*/



KeyPointsFilterBySizeProperties::KeyPointsFilterBySizeProperties()
  : KeyPointsFilter(KeyPointsFilter::Type::size),
    mMinSize(0.),
    mMaxSize(TL_DOUBLE_MAX)
{
}

double KeyPointsFilterBySizeProperties::minSize() const
{
  return mMinSize;
}

void KeyPointsFilterBySizeProperties::setMinSize(double minSize)
{
  mMinSize = minSize;
}

double KeyPointsFilterBySizeProperties::maxSize() const
{
  return mMaxSize;
}

void KeyPointsFilterBySizeProperties::setMaxSize(double maxSize)
{
  mMaxSize = maxSize;
}

void KeyPointsFilterBySizeProperties::reset()
{
  mMinSize = 0.;
  mMaxSize = TL_DOUBLE_MAX;
}


/*----------------------------------------------------------------*/


KeyPointsFilterBySize::KeyPointsFilterBySize()
{

}

KeyPointsFilterBySize::KeyPointsFilterBySize(double minSize, double maxSize)
  : KeyPointsFilterBySizeProperties()
{
  this->setMinSize(minSize);
  this->setMaxSize(maxSize);
}

void KeyPointsFilterBySize::setMinSize(double minSize)
{
  KeyPointsFilterBySizeProperties::setMinSize(minSize);
}

void KeyPointsFilterBySize::setMaxSize(double maxSize)
{
  KeyPointsFilterBySizeProperties::setMaxSize(maxSize);
}

bool KeyPointsFilterBySize::filter(const std::vector<cv::KeyPoint> &keypoints, std::vector<cv::KeyPoint> &filteredKeypoints)
{
  try {
    filteredKeypoints = keypoints;
    size_t size = keypoints.size();
    double min_size = KeyPointsFilterBySizeProperties::minSize();
    double max_size = KeyPointsFilterBySizeProperties::maxSize();
    cv::KeyPointsFilter::runByKeypointSize(filteredKeypoints, static_cast<float>(min_size), static_cast<float>(max_size));
    size_t new_size = filteredKeypoints.size();
    msgInfo("Filtered keypoints by size (min=%f,max=%f): %i", min_size, max_size, size - new_size);
    return false;
  } catch (cv::Exception &e) {
    msgError("Filtered keypoints error: %s", e.what());
    return true;
  }
}

void KeyPointsFilterBySize::reset()
{
  KeyPointsFilterBySizeProperties::reset();
}


/*----------------------------------------------------------------*/


KeyPointsFilterRemoveDuplicated::KeyPointsFilterRemoveDuplicated()
  : KeyPointsFilter(KeyPointsFilter::Type::remove_duplicated)
{

}

bool KeyPointsFilterRemoveDuplicated::filter(const std::vector<cv::KeyPoint>& keypoints, std::vector<cv::KeyPoint>& filteredKeypoints)
{
  try {
    filteredKeypoints = keypoints;
    int size = static_cast<int>(keypoints.size());
    cv::KeyPointsFilter::removeDuplicated(filteredKeypoints);
    int new_size = static_cast<int>(filteredKeypoints.size());
    msgInfo("Remove duplicated keypoints: %i", size - new_size);
    return false;
  } catch (cv::Exception &e) {
    msgError("Filtered keypoints error: %s", e.what());
    return true;
  }
}

void KeyPointsFilterRemoveDuplicated::reset()
{
}

} // namespace photomatch







