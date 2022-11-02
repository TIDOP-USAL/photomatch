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

#ifndef PHOTOMATCH_BRUTE_FORCE_MATCHER_H
#define PHOTOMATCH_BRUTE_FORCE_MATCHER_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/matcher.h"

#ifdef HAVE_OPENCV_CUDAFEATURES2D
#include <opencv2/cudafeatures2d.hpp>
#endif // HAVE_OPENCV_CUDAFEATURES2D

#include <vector>

namespace photomatch
{

class PHOTOMATCH_EXPORT BruteForceMatcherProperties
  : public BruteForceMatcher
{

public:

  BruteForceMatcherProperties();
  ~BruteForceMatcherProperties() override = default;

// Match interface

public:

  void reset() override;
  QString name() const final;

// IBruteForceMatcher interface

public:

  Norm normType() const override;
  void setNormType(Norm normType) override;

private:

  Norm mNormType;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT BruteForceMatcherImp
  : public BruteForceMatcherProperties,
    public DescriptorMatcher
{

public:

  BruteForceMatcherImp();
  explicit BruteForceMatcherImp(Norm normType);
  ~BruteForceMatcherImp() override = default;

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

// IBruteForceMatcher interface

public:

  void setNormType(Norm normType) override;

protected:

  cv::Ptr<cv::BFMatcher> mBFMatcher;
};


/*----------------------------------------------------------------*/


#ifdef HAVE_OPENCV_CUDAFEATURES2D

class PHOTOMATCH_EXPORT BruteForceMatcherCuda
  : public BruteForceMatcherProperties,
    public DescriptorMatcher
{

public:

  BruteForceMatcherCuda();
  explicit BruteForceMatcherCuda(Norm normType);
  ~BruteForceMatcherCuda() override = default;

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

// IBruteForceMatcher interface

public:

  void setNormType(Norm normType) override;

protected:

  cv::Ptr<cv::cuda::DescriptorMatcher> mBFMatcher;
};

#endif // HAVE_OPENCV_CUDAFEATURES2D

} // namespace photomatch

#endif // PHOTOMATCH_BRUTE_FORCE_MATCHER_H
