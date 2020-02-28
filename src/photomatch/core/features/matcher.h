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
#ifdef HAVE_CUDA
#include <opencv2/cudafeatures2d.hpp>
#endif // HAVE_CUDA

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

  MatchingMethod(Type type) : mMatchType(type) {}
  virtual ~MatchingMethod() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  /*!
   * \brief Type of match method (flann or brute force)
   * \return
   */
  Type type() const { return mMatchType.flags(); }

  /*!
   * \brief Name of match method
   * \return
   */
  virtual QString name() const = 0;

protected:

  tl::EnumFlags<Type> mMatchType;

};
ALLOW_BITWISE_FLAG_OPERATIONS(MatchingMethod::Type)


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
  virtual bool match(cv::InputArray &queryDescriptors,
                     cv::InputArray &trainDescriptors,
                     std::vector<cv::DMatch> &matches,
                     cv::InputArray mask = cv::noArray()) = 0;

  /*!
   * \brief Compute matching
   * \param[in] queryDescriptors Query descriptors
   * \param[in] trainDescriptors Train descriptors
   * \param[out] matches Matches 1 to 2 and 2 to 1
   * \param[in] mask
   * \return true if error
   */
  virtual bool match(cv::InputArray &queryDescriptors,
                     cv::InputArray &trainDescriptors,
                     std::vector<std::vector<cv::DMatch>> &matches,
                     cv::InputArray mask = cv::noArray()) = 0;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT FlannMatcher
  : public MatchingMethod
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

  FlannMatcher() : MatchingMethod(MatchingMethod::Type::flann) {}
  ~FlannMatcher() override = default;

  virtual Index index() const = 0;
  virtual void setIndex(Index index) = 0;

};

/*----------------------------------------------------------------*/

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

  bool match(cv::InputArray &queryDescriptors,
             cv::InputArray &trainDescriptors,
             std::vector<cv::DMatch> &matches,
             cv::InputArray mask = cv::noArray()) override;

  bool match(cv::InputArray &queryDescriptors,
             cv::InputArray &trainDescriptors,
             std::vector<std::vector<cv::DMatch>> &matches,
             cv::InputArray mask = cv::noArray()) override;

// Match interface

public:

  void reset() override;

// IFlannMatcher interface

public:

  void setIndex(Index index) override;

protected:

  cv::Ptr<cv::FlannBasedMatcher> mFlannBasedMatcher;

};

/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT BruteForceMatcher
  : public MatchingMethod
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

  BruteForceMatcher() : MatchingMethod(MatchingMethod::Type::brute_force) {}
  ~BruteForceMatcher() override = default;

  virtual Norm normType() const = 0;
  virtual void setNormType(Norm normType) = 0;

};

/*----------------------------------------------------------------*/

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

  bool match(cv::InputArray &queryDescriptors,
             cv::InputArray &trainDescriptors,
             std::vector<cv::DMatch> &matches,
             cv::InputArray mask = cv::noArray()) override;

  bool match(cv::InputArray &queryDescriptors,
             cv::InputArray &trainDescriptors,
             std::vector<std::vector<cv::DMatch>> &matches,
             cv::InputArray mask = cv::noArray()) override;

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

#ifdef HAVE_CUDA

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

  bool match(cv::InputArray &queryDescriptors,
             cv::InputArray &trainDescriptors,
             std::vector<cv::DMatch> &matches,
             cv::InputArray mask = cv::noArray()) override;

  bool match(cv::InputArray &queryDescriptors,
             cv::InputArray &trainDescriptors,
             std::vector<std::vector<cv::DMatch>> &matches,
             cv::InputArray mask = cv::noArray()) override;

// Match interface

public:

  void reset() override;

// IBruteForceMatcher interface

public:

  void setNormType(Norm normType) override;

protected:

  cv::Ptr<cv::cuda::DescriptorMatcher> mBFMatcher;
};

#endif // HAVE_CUDA



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

  MatchingStrategy(Strategy strategy) : mStrategy(strategy) {}
  virtual ~MatchingStrategy() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  Strategy strategy() const { return mStrategy.flags(); }
  virtual QString name() const = 0;

protected:

  tl::EnumFlags<Strategy> mStrategy;

};
ALLOW_BITWISE_FLAG_OPERATIONS(MatchingStrategy::Strategy)


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
  : public MatchingStrategy
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

  RobustMatcher()
    : MatchingStrategy(MatchingStrategy::Strategy::robust_matching) {}
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

  /*!
   * \brief Recover the default values
   */
  //virtual void reset() = 0;

};


/*----------------------------------------------------------------*/

class PHOTOMATCH_EXPORT RobustMatchingProperties
  : public RobustMatcher
{

public:

  RobustMatchingProperties();
  ~RobustMatchingProperties() override = default;

// IRobustMatcherRefinement interface

public:

  double ratio() const override;
  void setRatio(double ratio) override;
  bool crossCheck() const override;
  void setCrossCheck(bool crossCheck) override;
  GeometricTest geometricTest() const override;
  void setGeometricTest(GeometricTest geometricTest) override;
  HomographyComputeMethod homographyComputeMethod() const override;
  void setHomographyComputeMethod(HomographyComputeMethod computeMethod) override;
  FundamentalComputeMethod fundamentalComputeMethod() const override;
  void setFundamentalComputeMethod(FundamentalComputeMethod computeMethod) override;
  EssentialComputeMethod essentialComputeMethod() const override;
  void setEssentialComputeMethod(EssentialComputeMethod computeMethod) override;
  double distance() const override;
  void setDistance(double distance) override;
  double confidence() const override;
  void setConfidence(double confidence) override;
  int maxIter() const override;
  void setMaxIters(int maxIter) override;

// MatchingStrategy interface

public:

  void reset() override;
  QString name() const override;

private:

  double mRatio;
  bool mCrossCheck;
  GeometricTest mGeometricTest;
  HomographyComputeMethod mHomographyComputeMethod;
  FundamentalComputeMethod mFundamentalComputeMethod;
  EssentialComputeMethod mEssentialComputeMethod;
  double mDistance;
  double mConfidence;
  int mMaxIters;

};

/*----------------------------------------------------------------*/

class PHOTOMATCH_EXPORT RobustMatchingImp
  : public RobustMatchingProperties,
    public MatchingAlgorithm
{

public:

  explicit RobustMatchingImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher);
  RobustMatchingImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher,
                    double ratio,
                    bool crossCheck,
                    GeometricTest geometricTest,
                    HomographyComputeMethod homographyComputeMethod,
                    FundamentalComputeMethod fundamentalComputeMethod,
                    EssentialComputeMethod essentialComputeMethod,
                    double distance,
                    double confidence,
                    int maxIter);
  ~RobustMatchingImp() override = default;

  /*!
   * \brief Establece el metodo de matching
   * \param[in] matcher
   */
  void setDescriptorMatcher(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher);

  /*!
   * \brief Ratio test
   * \param[in] matches
   * \param[in] ratio
   * \param[out] goodMatches
   * \param[out] wrongMatches
   */
  static std::vector<std::vector<cv::DMatch>> ratioTest(const std::vector<std::vector<cv::DMatch>> &matches,
                        double ratio,
                        std::vector<std::vector<cv::DMatch>> *wrongMatches = nullptr)
  {
    std::vector<std::vector<cv::DMatch>> goodMatches;

    for (size_t i = 0; i < matches.size(); i++){

      if (matches[i].size() > 1){
        // check distance ratio
        if (matches[i][0].distance / matches[i][1].distance <= static_cast<float>(ratio)) {
            goodMatches.push_back(matches[i]);
        } else {
          if (wrongMatches){
            wrongMatches->push_back(matches[i]);
          }
        }
      }

    }

    return goodMatches;
  }

  /*!
   * \brief test cruzado
   * Busqueda de matches simétricos
   * \param[in] matches12
   * \param[in] matches21
   * \param[out] goodMatches
   * \param[out] wrongMatches
   */
  static std::vector<cv::DMatch> crossCheckTest(const std::vector<std::vector<cv::DMatch>> &matches12,
                                                const std::vector<std::vector<cv::DMatch>> &matches21,
                                                std::vector<cv::DMatch> *wrongMatches = nullptr)
  {
    std::vector<cv::DMatch> goodMatches;

    for (size_t i = 0; i < matches12.size(); i++){

      if (matches12[i].empty() || matches12[i].size() < 2)
        continue;

      bool findGoodMatch = false;
      for (size_t j = 0; j < matches21.size(); j++){

        if (matches21[j].empty() || matches21[j].size() < 2)
          continue;

        if (matches12[i][0].queryIdx == matches21[j][0].trainIdx &&
            matches21[j][0].queryIdx == matches12[i][0].trainIdx) {
            goodMatches.push_back(matches12[i][0]);
          findGoodMatch = true;
          break;
        }

      }

      if (findGoodMatch == false && wrongMatches)
        wrongMatches->push_back(matches12[i][0]);

    }

    return goodMatches;
  }

  std::vector<cv::DMatch> geometricFilter(const std::vector<cv::DMatch> &matches,
                                          const std::vector<cv::KeyPoint>& keypoints1,
                                          const std::vector<cv::KeyPoint>& keypoints2,
                                          std::vector<cv::DMatch> *wrongMatches = nullptr);

  std::vector<cv::DMatch> filterByHomographyMatrix(const std::vector<cv::DMatch> &matches,
                                                   const std::vector<cv::Point2f>& points1,
                                                   const std::vector<cv::Point2f>& points2,
                                                   std::vector<cv::DMatch> *wrongMatches = nullptr);
  std::vector<cv::DMatch> filterByEssentialMatrix(const std::vector<cv::DMatch> &matches,
                                                  const std::vector<cv::Point2f>& points1,
                                                  const std::vector<cv::Point2f>& points2,
                                                  std::vector<cv::DMatch> *wrongMatches = nullptr);
  std::vector<cv::DMatch> filterByFundamentalMatrix(const std::vector<cv::DMatch> &matches,
                                                    const std::vector<cv::Point2f>& points1,
                                                    const std::vector<cv::Point2f>& points2,
                                                    std::vector<cv::DMatch> *wrongMatches = nullptr);

  /*!
   * \brief Matching
   * \param[in] queryDescriptor Query descriptor
   * \param[in] trainDescriptor Train descriptor
   * \param[out] wrongMatches Wrong matches
   * \return Good matches
   */
  std::vector<cv::DMatch> match(const cv::Mat &queryDescriptor,
                                const cv::Mat &trainDescriptor,
                                std::vector<cv::DMatch> *wrongMatches = nullptr);

private:

  /*!
   * \brief Robust matching
   * Feature matching using ratio and symmetry tests
   * \param[in] queryDescriptor Query descriptor
   * \param[in] trainDescriptor Train descriptor
   * \param[out] wrongMatches Wrong matches
   * \return Good matches
   */
  std::vector<cv::DMatch> robustMatch(const cv::Mat &queryDescriptor,
                                      const cv::Mat &trainDescriptor,
                                      std::vector<cv::DMatch> *wrongMatches);

  /*!
   * \brief Robust matching
   * Feature matching using ratio test
   * \param[in] queryDescriptor Query descriptor
   * \param[in] trainDescriptor Train descriptor
   * \param[out] wrongMatches Wrong matches
   * \return Good matches
   */
  std::vector<cv::DMatch> fastRobustMatch(const cv::Mat &queryDescriptor,
                                          const cv::Mat &trainDescriptor,
                                          std::vector<cv::DMatch> *wrongMatches);


// MatchingAlgorithm interface

public:

  bool compute(const cv::Mat &queryDescriptor,
               const cv::Mat &trainDescriptor,
               const std::vector<cv::KeyPoint> &keypoints1,
               const std::vector<cv::KeyPoint> &keypoints2,
               std::vector<cv::DMatch> *goodMatches,
               std::vector<cv::DMatch> *wrongMatches = nullptr,
               const QSize &queryImageSize = QSize(),
               const QSize &trainImageSize = QSize()) override;

protected:

  std::shared_ptr<DescriptorMatcher> mDescriptorMatcher;

};

/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT Gms
  : public MatchingStrategy
{

public:

  Gms() : MatchingStrategy(MatchingStrategy::Strategy::gms) {}
  ~Gms() override = default;

  virtual bool rotation() const = 0;
  virtual void setRotation(bool rotation) = 0;

  virtual bool scale() const  = 0;
  virtual void setScale(bool scale) = 0;

  virtual double threshold() const = 0;
  virtual void setThreshold(double threshold) = 0;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT GmsProperties
  : public Gms
{

public:

  GmsProperties();
  ~GmsProperties() override = default;


// MatchingStrategy interface

public:

  void reset() override;
  QString name() const override;

// IGms interface

public:

  bool rotation() const override;
  void setRotation(bool rotation) override;
  bool scale() const override;
  void setScale(bool scale) override;
  double threshold() const override;
  void setThreshold(double threshold) override;

protected:

  bool mRotation;
  bool mScale;
  double mThreshold;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT GsmImp
  : public GmsProperties,
    public MatchingAlgorithm
{

public:

  explicit GsmImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher);
  GsmImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher,
         bool rotation,
         bool scale,
         double threshold);
  ~GsmImp() override = default;

// MatchingAlgorithm interface

public:

  bool compute(const cv::Mat &queryDescriptor,
               const cv::Mat &trainDescriptor,
               const std::vector<cv::KeyPoint> &keypoints1,
               const std::vector<cv::KeyPoint> &keypoints2,
               std::vector<cv::DMatch> *goodMatches,
               std::vector<cv::DMatch> *wrongMatches = nullptr,
               const QSize &queryImageSize = QSize(),
               const QSize &trainImageSize = QSize()) override;

protected:

  std::shared_ptr<DescriptorMatcher> mDescriptorMatcher;

};


/*----------------------------------------------------------------*/


/*!
 * \brief Pass Points write
 * \param[in] fname File name
 * \param[in] pass_points Pass Points
 */
PHOTOMATCH_EXPORT void passPointsWrite(const QString &fname,
                                       const std::vector<std::vector<std::pair<QString,int>>> &pass_points);

/*!
 * \brief Pass Points read
 * \param[in] fname File name
 * \param[out] pass_points Pass Points
 */
PHOTOMATCH_EXPORT void passPointsRead(const QString &fname,
                                      std::vector<std::vector<std::pair<QString,int>>> &pass_points);


/*----------------------------------------------------------------*/


} // namespace photomatch

Q_DECLARE_METATYPE(photomatch::BruteForceMatcher::Norm)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::GeometricTest)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::HomographyComputeMethod)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::FundamentalComputeMethod)
Q_DECLARE_METATYPE(photomatch::RobustMatcher::EssentialComputeMethod)

#endif // PHOTOMATCH_MATCHER_H
