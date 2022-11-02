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

#include "bfmatch.h"

#include <tidop/core/messages.h>

namespace photomatch
{


BruteForceMatcherProperties::BruteForceMatcherProperties()
  : mNormType(BruteForceMatcherProperties::Norm::l2)
{
}

void BruteForceMatcherProperties::reset()
{
  mNormType = BruteForceMatcherProperties::Norm::l2;
}

QString BruteForceMatcherProperties::name() const
{
  return QString("Brute Force Matching");
}

BruteForceMatcherProperties::Norm BruteForceMatcherProperties::normType() const
{
  return mNormType;
}

void BruteForceMatcherProperties::setNormType(BruteForceMatcher::Norm normType)
{
  mNormType = normType;
}

/*----------------------------------------------------------------*/


BruteForceMatcherImp::BruteForceMatcherImp()
{
  update();
}

BruteForceMatcherImp::BruteForceMatcherImp(BruteForceMatcher::Norm normType)
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

void BruteForceMatcherImp::update()
{
  int norm = cv::NORM_L2;
  BruteForceMatcherProperties::Norm norm_type = BruteForceMatcherProperties::normType();
  if (norm_type == BruteForceMatcherProperties::Norm::l1) {
    norm = cv::NORM_L1;
  } else if (norm_type == BruteForceMatcherProperties::Norm::l2) {
    norm = cv::NORM_L2;
  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming) {
    norm = cv::NORM_HAMMING;
  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming2) {
    norm = cv::NORM_HAMMING2;
  }

  try {
    mBFMatcher = cv::BFMatcher::create(norm);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
  }
}

bool BruteForceMatcherImp::match(const cv::Mat &queryDescriptors,
                                 const cv::Mat &trainDescriptors,
                                 std::vector<cv::DMatch> &matches,
                                 const cv::Mat &mask)
{
  try {
    mBFMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
    return true;
  }
  return false;
}

bool BruteForceMatcherImp::match(const cv::Mat &queryDescriptors,
                                 const cv::Mat &trainDescriptors,
                                 std::vector<std::vector<cv::DMatch>> &matches,
                                 const cv::Mat &mask)
{
  try {
    mBFMatcher->knnMatch(queryDescriptors, trainDescriptors, matches, 2, mask);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
    return true;
  }
  return false;
}

void BruteForceMatcherImp::reset()
{
  BruteForceMatcherProperties::reset();
  update();
}

void BruteForceMatcherImp::setNormType(BruteForceMatcher::Norm normType)
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

/*----------------------------------------------------------------*/

#ifdef HAVE_OPENCV_CUDAFEATURES2D

BruteForceMatcherCuda::BruteForceMatcherCuda()
{
  update();
}

BruteForceMatcherCuda::BruteForceMatcherCuda(BruteForceMatcher::Norm normType)
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

void BruteForceMatcherCuda::update()
{
  int norm = cv::NORM_L2;
  BruteForceMatcherProperties::Norm norm_type = BruteForceMatcherProperties::normType();
  if (norm_type == BruteForceMatcherProperties::Norm::l1) {
    norm = cv::NORM_L1;
  } else if (norm_type == BruteForceMatcherProperties::Norm::l2) {
    norm = cv::NORM_L2;
  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming) {
    norm = cv::NORM_HAMMING;
  }
  ///La implementación de BFMatcher con Cuda no incluye NORM_HAMMING2
  /*else if (norm_type == BruteForceMatcherProperties::Norm::hamming2) {
    norm = cv::NORM_HAMMING2;
  }*/

  try {
    mBFMatcher = cv::cuda::DescriptorMatcher::createBFMatcher(norm);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
  }
}

bool BruteForceMatcherCuda::match(const cv::Mat &queryDescriptors,
                                  const cv::Mat &trainDescriptors,
                                  std::vector<cv::DMatch> &matches,
                                  const cv::Mat &mask)
{
  try {
    cv::cuda::GpuMat gQueryDescriptors(queryDescriptors);
    cv::cuda::GpuMat gTrainDescriptors(trainDescriptors);
    cv::cuda::GpuMat gMask(mask);
    mBFMatcher->match(gQueryDescriptors, gTrainDescriptors, matches, gMask);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
    return true;
  }
  return false;
}

bool BruteForceMatcherCuda::match(const cv::Mat &queryDescriptors,
                                  const cv::Mat &trainDescriptors,
                                  std::vector<std::vector<cv::DMatch>> &matches,
                                  const cv::Mat &mask)
{
  try {
    cv::cuda::GpuMat gQueryDescriptors(queryDescriptors);
    cv::cuda::GpuMat gTrainDescriptors(trainDescriptors);
    cv::cuda::GpuMat gMask(mask);
    mBFMatcher->knnMatch(gQueryDescriptors, gTrainDescriptors, matches, 2, gMask);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
    return true;
  }
  return false;
}

void BruteForceMatcherCuda::reset()
{
  BruteForceMatcherProperties::reset();
  update();
}

void BruteForceMatcherCuda::setNormType(BruteForceMatcher::Norm normType)
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

#endif // HAVE_OPENCV_CUDAFEATURES2D

} // namespace photomatch
