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

#include "gsm.h"

#include <tidop/core/messages.h>

namespace photomatch
{

GmsProperties::GmsProperties()
  : mRotation(true),
    mScale(true),
    mThreshold(6.)
{

}

void GmsProperties::reset()
{
  mRotation = true;
  mScale = true;
  mThreshold = 6.;
}

QString GmsProperties::name() const
{
  return QString("GMS");
}

bool GmsProperties::rotation() const
{
  return mRotation;
}

void GmsProperties::setRotation(bool rotation)
{
  mRotation = rotation;
}

bool GmsProperties::scale() const
{
  return mScale;
}

void GmsProperties::setScale(bool scale)
{
  mScale = scale;
}

double GmsProperties::threshold() const
{
  return mThreshold;
}

void GmsProperties::setThreshold(double threshold)
{
  mThreshold = threshold;
}

/*----------------------------------------------------------------*/


GsmImp::GsmImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher)
  : GmsProperties(),
    mDescriptorMatcher(descriptorMatcher)
{
}

GsmImp::GsmImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher,
               bool rotation,
               bool scale,
               double threshold)
  : GmsProperties(),
    mDescriptorMatcher(descriptorMatcher)
{
  this->setRotation(rotation);
  this->setScale(scale);
  this->setThreshold(threshold);
}

bool GsmImp::compute(const cv::Mat &queryDescriptor,
                     const cv::Mat &trainDescriptor,
                     const std::vector<cv::KeyPoint> &keypoints1,
                     const std::vector<cv::KeyPoint> &keypoints2,
                     std::vector<cv::DMatch> *goodMatches,
                     std::vector<cv::DMatch> *wrongMatches,
                     const QSize &queryImageSize,
                     const QSize &trainImageSize)
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR >= 4 && CV_VERSION_REVISION >= 1 )
  try {

    if (goodMatches == nullptr) return true;

    std::vector<cv::DMatch> matches;
    bool err = mDescriptorMatcher->match(queryDescriptor, trainDescriptor, matches);
    if (err) return true;

    cv::Size img1Size(queryImageSize.width(), queryImageSize.height());
    cv::Size img2Size(trainImageSize.width(), trainImageSize.height());
    cv::xfeatures2d::matchGMS(img1Size, img2Size, keypoints1, keypoints2, matches, *goodMatches);

    for (size_t i = 0; i < matches.size(); i++) {
      bool bWrong = true;
      for (size_t j = 0; j < goodMatches->size(); j++) {
        if (matches[i].queryIdx == (*goodMatches)[j].queryIdx &&
            matches[i].trainIdx == (*goodMatches)[j].trainIdx) {
          bWrong = false;
          break;
        }
      }
      if (bWrong) {
        wrongMatches->push_back(matches[i]);
      }
    }

    /// TODO: devolver wrongMatches

  } catch(std::exception &e){
    msgError(e.what());
    return true;
  }
#  else
  Q_UNUSED(queryDescriptor)
  Q_UNUSED(trainDescriptor)
  Q_UNUSED(keypoints1)
  Q_UNUSED(keypoints2)
  Q_UNUSED(goodMatches)
  Q_UNUSED(wrongMatches)
  Q_UNUSED(queryImageSize)
  Q_UNUSED(trainImageSize)
  TL_COMPILER_WARNING("'matchGMS' not supported in OpenCV versions < 3.3.1")
#endif
  return false;
}

} // namespace photomatch
