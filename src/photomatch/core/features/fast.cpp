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


#include "fast.h"

#include <tidop/core/messages.h>


namespace photomatch
{


FastProperties::FastProperties()
  : mThreshold(10),
    mNonmaxSuppression(true),
    mDetectorType("TYPE_9_16")
{
}

FastProperties::FastProperties(const FastProperties &fastProperties)
  : Fast(fastProperties),
    mThreshold(fastProperties.mThreshold),
    mNonmaxSuppression(fastProperties.mNonmaxSuppression),
    mDetectorType(fastProperties.mDetectorType)
{
}

int FastProperties::threshold() const
{
  return mThreshold;
}

bool FastProperties::nonmaxSuppression() const
{
  return mNonmaxSuppression;
}

QString FastProperties::detectorType() const
{
  return mDetectorType;
}

void FastProperties::setThreshold(int threshold)
{
  mThreshold = threshold;
}

void FastProperties::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression = nonmaxSuppression;
}

void FastProperties::setDetectorType(const QString &detectorType)
{
  mDetectorType = detectorType;
}

void FastProperties::reset()
{
  mThreshold = 10;
  mNonmaxSuppression = true;
  mDetectorType = "TYPE_9_16";
}

QString FastProperties::name() const
{
  return QString("FAST");
}


/*----------------------------------------------------------------*/


FastDetector::FastDetector()
{
  mFast = cv::FastFeatureDetector::create(FastProperties::threshold(),
                                          FastProperties::nonmaxSuppression(),
                                          convertDetectorType(FastProperties::detectorType()));
}

FastDetector::FastDetector(const FastDetector &fastDetector)
  : FastProperties(fastDetector),
    KeypointDetector(fastDetector)
{
  mFast = cv::FastFeatureDetector::create(FastProperties::threshold(),
                                          FastProperties::nonmaxSuppression(),
                                          convertDetectorType(FastProperties::detectorType()));
}

FastDetector::FastDetector(int threshold,
                           bool nonmaxSuppression,
                           const QString &detectorType)
  : mFast(cv::FastFeatureDetector::create())
{
  this->setThreshold(threshold);
  this->setNonmaxSuppression(nonmaxSuppression);
  this->setDetectorType(detectorType);
}


#if CV_VERSION_MAJOR >= 4
cv::FastFeatureDetector::DetectorType FastDetector::convertDetectorType(const QString &detectorType)
{
  cv::FastFeatureDetector::DetectorType type = cv::FastFeatureDetector::DetectorType::TYPE_9_16;

  if (detectorType.compare("TYPE_5_8") == 0){
    type = cv::FastFeatureDetector::TYPE_5_8;
  } else if (detectorType.compare("TYPE_7_12") == 0) {
    type = cv::FastFeatureDetector::TYPE_7_12;
  } else if (detectorType.compare("TYPE_9_16") == 0) {
    type = cv::FastFeatureDetector::TYPE_9_16;
  }

  return type;
}

#else

int FastDetector::convertDetectorType(const QString &detectorType)
{
  int type = cv::FastFeatureDetector::TYPE_9_16;

  if (detectorType.compare("TYPE_5_8") == 0){
    type = cv::FastFeatureDetector::TYPE_5_8;
  } else if (detectorType.compare("TYPE_7_12") == 0) {
    type = cv::FastFeatureDetector::TYPE_7_12;
  } else if (detectorType.compare("TYPE_9_16") == 0) {
    type = cv::FastFeatureDetector::TYPE_9_16;
  }

  return type;
}
#endif

bool FastDetector::detect(const cv::Mat &img,
                          std::vector<cv::KeyPoint> &keyPoints,
                          cv::InputArray &mask)
{

  try {
    mFast->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("FAST Detector error: %s", e.what());
    return true;
  }

  return false;
}

void FastDetector::setThreshold(int threshold)
{
  FastProperties::setThreshold(threshold);
  mFast->setThreshold(threshold);
}

void FastDetector::setNonmaxSuppression(bool nonmaxSuppression)
{
  FastProperties::setNonmaxSuppression(nonmaxSuppression);
  mFast->setNonmaxSuppression(nonmaxSuppression);
}

void FastDetector::setDetectorType(const QString &detectorType)
{
  FastProperties::setDetectorType(detectorType);
  mFast->setType(convertDetectorType(detectorType));
}

void FastDetector::reset()
{
  FastProperties::reset();
  mFast->setThreshold(FastProperties::threshold());
  mFast->setNonmaxSuppression(FastProperties::nonmaxSuppression());
  mFast->setType(convertDetectorType(FastProperties::detectorType()));
}


/*----------------------------------------------------------------*/

#ifdef HAVE_OPENCV_CUDAFEATURES2D

FastDetectorCuda::FastDetectorCuda()
{
  this->update();
}

FastDetectorCuda::FastDetectorCuda(const FastDetector &fastDetector)
  : FastProperties(fastDetector),
    KeypointDetector(fastDetector)
{
  this->update();
}

FastDetectorCuda::FastDetectorCuda(int threshold,
                                   bool nonmaxSuppression,
                                   const QString &detectorType)
{
  FastProperties::setThreshold(threshold);
  FastProperties::setNonmaxSuppression(nonmaxSuppression);
  FastProperties::setDetectorType(detectorType);
  this->update();
}


//#if CV_VERSION_MAJOR >= 4
//cv::FastFeatureDetector::DetectorType FastDetectorCuda::convertDetectorType(const QString &detectorType)
//{
//  cv::FastFeatureDetector::DetectorType type = cv::FastFeatureDetector::DetectorType::TYPE_9_16;

//  if (detectorType.compare("TYPE_5_8") == 0){
//    type = cv::FastFeatureDetector::TYPE_5_8;
//  } else if (detectorType.compare("TYPE_7_12") == 0) {
//    type = cv::FastFeatureDetector::TYPE_7_12;
//  } else if (detectorType.compare("TYPE_9_16") == 0) {
//    type = cv::FastFeatureDetector::TYPE_9_16;
//  }

//  return type;
//}

//#else

int FastDetectorCuda::convertDetectorType(const QString &detectorType)
{
  int type = cv::FastFeatureDetector::TYPE_9_16;

  if (detectorType.compare("TYPE_5_8") == 0){
    type = cv::FastFeatureDetector::TYPE_5_8;
  } else if (detectorType.compare("TYPE_7_12") == 0) {
    type = cv::FastFeatureDetector::TYPE_7_12;
  } else if (detectorType.compare("TYPE_9_16") == 0) {
    type = cv::FastFeatureDetector::TYPE_9_16;
  }

  return type;
}
//#endif

void FastDetectorCuda::update()
{
  mFast = cv::cuda::FastFeatureDetector::create(FastProperties::threshold(),
                                                FastProperties::nonmaxSuppression(),
                                                convertDetectorType(FastProperties::detectorType()),
                                                10000);
}

bool FastDetectorCuda::detect(const cv::Mat &img,
                              std::vector<cv::KeyPoint> &keyPoints,
                              cv::InputArray &mask)
{

  try {
    cv::cuda::GpuMat g_img(img);
    cv::cuda::GpuMat g_mask(mask);
    mFast->detect(g_img, keyPoints, g_mask);
  } catch (cv::Exception &e) {
    msgError("FAST Detector error: %s", e.what());
    return true;
  }

  return false;
}

void FastDetectorCuda::setThreshold(int threshold)
{
  FastProperties::setThreshold(threshold);
  update();
}

void FastDetectorCuda::setNonmaxSuppression(bool nonmaxSuppression)
{
  FastProperties::setNonmaxSuppression(nonmaxSuppression);
  update();
}

void FastDetectorCuda::setDetectorType(const QString &detectorType)
{
  FastProperties::setDetectorType(detectorType);
  update();
}

void FastDetectorCuda::reset()
{
  FastProperties::reset();
  update();
}

#endif // HAVE_OPENCV_CUDAFEATURES2D


} // namespace photomatch
