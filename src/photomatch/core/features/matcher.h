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


#ifndef PHOTOMATCH_MATCHER_H
#define PHOTOMATCH_MATCHER_H

#include "photomatch/photomatch_global.h"

#include <memory>

#include <QString>
#include <QObject>
#include <QSize>

#include <opencv2/xfeatures2d.hpp>

#include <tidop/core/flags.h>


namespace photomatch
{


class PHOTOMATCH_EXPORT MatchingMethod
{

public:

  enum class Type
  {
    flann,
    brute_force
  };

public:

  MatchingMethod() {}
  virtual ~MatchingMethod() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  /*!
   * \brief Type of match method (flann or brute force)
   * \return
   */
  virtual Type type() const = 0;

  /*!
   * \brief Name of match method
   * \return
   */
  virtual QString name() const = 0;

};
ALLOW_BITWISE_FLAG_OPERATIONS(MatchingMethod::Type)


class MatchingMethodBase
  : public MatchingMethod
{

public:

  MatchingMethodBase(Type type) : mMatchType(type) {}
  ~MatchingMethodBase() override = default;

// MatchingMethod interface

public:

  Type type() const override 
  { 
    return mMatchType.flags(); 
  }

protected:

  tl::EnumFlags<Type> mMatchType;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT DescriptorMatcher
{

public:

  DescriptorMatcher() {}
  virtual ~DescriptorMatcher() = default;

public:

  /*!
   * \brief Compute matching
   * \param[in] queryDescriptors Query descriptors
   * \param[in] trainDescriptors Train descriptors
   * \param[out] matches Matches 1 to 2
   * \param[in] mask
   * \return
   */
  virtual bool match(const cv::Mat &queryDescriptors,
                     const cv::Mat &trainDescriptors,
                     std::vector<cv::DMatch> &matches,
                     const cv::Mat &mask = cv::Mat()) = 0;

  /*!
   * \brief Compute matching
   * \param[in] queryDescriptors Query descriptors
   * \param[in] trainDescriptors Train descriptors
   * \param[out] matches Matches 1 to 2 and 2 to 1
   * \param[in] mask
   * \return true if error
   */
  virtual bool match(const cv::Mat &queryDescriptors,
                     const cv::Mat &trainDescriptors,
                     std::vector<std::vector<cv::DMatch>> &matches,
                     const cv::Mat &mask = cv::Mat()) = 0;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT FlannMatcher
  : public MatchingMethodBase
{

public:

  /// TODO: Por ahora valores por defecto
  enum class Index
  {
    kdtree,
    lsh
    ///TODO: https://docs.opencv.org/4.1.1/db/df4/structcv_1_1flann_1_1IndexParams.html
  };

public:

  FlannMatcher() : MatchingMethodBase(Type::flann) {}
  ~FlannMatcher() override = default;

  virtual Index index() const = 0;
  virtual void setIndex(Index index) = 0;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT BruteForceMatcher
  : public MatchingMethodBase
{
public:

  enum class Norm
  {
    l1,
    l2,
    hamming,
    hamming2
  };

public:

  BruteForceMatcher() : MatchingMethodBase(MatchingMethod::Type::brute_force) {}
  ~BruteForceMatcher() override = default;

  virtual Norm normType() const = 0;
  virtual void setNormType(Norm normType) = 0;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT MatchingStrategy
{
public:

  enum class Strategy
  {
    robust_matching,
    gms
  };

public:

  MatchingStrategy() {}
  virtual ~MatchingStrategy() = default;

  virtual void reset() = 0;
  virtual Strategy strategy() const = 0;
  virtual QString name() const = 0;

};
ALLOW_BITWISE_FLAG_OPERATIONS(MatchingStrategy::Strategy)


class MatchingStrategyBase
  : public MatchingStrategy
{

public:
  
  MatchingStrategyBase(Strategy strategy) : mStrategy(strategy) {}
  ~MatchingStrategyBase() override = default;

// MatchingStrategy interface

public:

  Strategy strategy() const override
  { 
    return mStrategy.flags(); 
  }

protected:

  tl::EnumFlags<Strategy> mStrategy;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT MatchingAlgorithm
{

public:

  MatchingAlgorithm() {}
  virtual ~MatchingAlgorithm() = default;

  virtual bool compute(const cv::Mat &queryDescriptor,
                       const cv::Mat &trainDescriptor,
                       const std::vector<cv::KeyPoint> &keypoints1,
                       const std::vector<cv::KeyPoint> &keypoints2,
                       std::vector<cv::DMatch> *goodMatches,
                       std::vector<cv::DMatch> *wrongMatches = nullptr,
                       const QSize &queryImageSize = QSize(),
                       const QSize &trainImageSize = QSize()) = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief The IRobustMatcherRefinement class
 *
 * Robust Matching:
 *
 * http://docs.opencv.org/3.1.0/dc/d2c/tutorial_real_time_pose.html
 */
class PHOTOMATCH_EXPORT RobustMatcher
  : public MatchingStrategyBase
{

public:

  enum class GeometricTest
  {
    homography,
    fundamental,
    essential
  };

  enum class HomographyComputeMethod
  {
    all_points,
    ransac,
    lmeds,
    rho
  };

  enum class FundamentalComputeMethod
  {
    algorithm_7_point,
    algorithm_8_point,
    ransac,
    lmeds
  };

  enum class EssentialComputeMethod
  {
    ransac,
    lmeds
  };

public:

  RobustMatcher() : MatchingStrategyBase(Strategy::robust_matching) {}
  ~RobustMatcher() override = default;

  virtual double ratio() const = 0;
  virtual void setRatio(double ratio) = 0;

  virtual bool crossCheck() const = 0;
  virtual void setCrossCheck(bool crossCheck) = 0;

  virtual GeometricTest geometricTest() const = 0;
  virtual void setGeometricTest(GeometricTest geometricTest) = 0;

  virtual HomographyComputeMethod homographyComputeMethod() const = 0;
  virtual void setHomographyComputeMethod(HomographyComputeMethod computeMethod) = 0;

  virtual FundamentalComputeMethod fundamentalComputeMethod() const = 0;
  virtual void setFundamentalComputeMethod(FundamentalComputeMethod computeMethod) = 0;

  virtual EssentialComputeMethod essentialComputeMethod() const = 0;
  virtual void setEssentialComputeMethod(EssentialComputeMethod computeMethod) = 0;

  virtual double distance() const = 0;
  virtual void setDistance(double distance) = 0;

  virtual double confidence() const = 0;
  virtual void setConfidence(double confidence) = 0;

  virtual int maxIter() const = 0;
  virtual void setMaxIters(int maxIter) = 0;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT Gms
  : public MatchingStrategyBase
{

public:

  Gms() : MatchingStrategyBase(Strategy::gms) {}
  ~Gms() override = default;

  virtual bool rotation() const = 0;
  virtual void setRotation(bool rotation) = 0;

  virtual bool scale() const  = 0;
  virtual void setScale(bool scale) = 0;

  virtual double threshold() const = 0;
  virtual void setThreshold(double threshold) = 0;
};



} // namespace photomatch

Q_DECLARE_METATYPE(photomatch::BruteForceMatcher::Norm)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::GeometricTest)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::HomographyComputeMethod)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::FundamentalComputeMethod)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::EssentialComputeMethod)

#endif // PHOTOMATCH_MATCHER_H
