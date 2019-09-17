#ifndef FME_MATCHER_H
#define FME_MATCHER_H

#include "fme/fme_global.h"

#include <memory>

#include <QString>
#include <QObject>

#include <opencv2/xfeatures2d.hpp>
#ifdef HAVE_CUDA
#include <opencv2/cudafeatures2d.hpp>
#endif // HAVE_CUDA

#include <tidop/core/flags.h>


namespace fme
{


class FME_EXPORT Match
{

public:

  enum class Type
  {
    flann,
    brute_force
  };

public:

  Match(Type type) : mMatchType(type) {}
  virtual ~Match() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  Type type() const { return mMatchType.flags(); }
  virtual QString name() const = 0;

protected:

  tl::EnumFlags<Type> mMatchType;

};
ALLOW_BITWISE_FLAG_OPERATIONS(Match::Type)


/*----------------------------------------------------------------*/


class FME_EXPORT DescriptorMatcher
{

public:

  DescriptorMatcher() {}
  virtual ~DescriptorMatcher() = default;

public:

  virtual std::vector<std::vector<cv::DMatch>> match(cv::InputArray &queryDescriptors,
                                                     cv::InputArray &trainDescriptors,
                                                     cv::InputArray mask = cv::noArray()) = 0;

};


/*----------------------------------------------------------------*/


class FME_EXPORT IFlannMatcher
  : public Match
{

public:
  IFlannMatcher() : Match(Match::Type::flann) {}
  virtual ~IFlannMatcher() override = default;

};

/*----------------------------------------------------------------*/

class FME_EXPORT FlannMatcherProperties
  : public IFlannMatcher
{

public:

  FlannMatcherProperties();
  virtual ~FlannMatcherProperties() override;

// Match interface

public:

  virtual void reset() override;
  QString name() const final;
};

/*----------------------------------------------------------------*/

class FME_EXPORT FlannMatcher
  : public FlannMatcherProperties,
    public DescriptorMatcher
{

public:

  FlannMatcher();
  ~FlannMatcher() override;

// DescriptorMatcher interface

public:

  std::vector<std::vector<cv::DMatch>> match(cv::InputArray &queryDescriptors,
                                             cv::InputArray &trainDescriptors,
                                             cv::InputArray mask = cv::noArray()) override;

// Match interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::FlannBasedMatcher> mFlannBasedMatcher;

};

/*----------------------------------------------------------------*/


class FME_EXPORT IBruteForceMatcher
  : public Match
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

  IBruteForceMatcher() : Match(Match::Type::brute_force) {}
  virtual ~IBruteForceMatcher() override = default;

public:

  virtual Norm normType() const = 0;
  virtual void setNormType(Norm normType) = 0;

};

/*----------------------------------------------------------------*/

class FME_EXPORT BruteForceMatcherProperties
  : public IBruteForceMatcher
{

public:

  BruteForceMatcherProperties();
  ~BruteForceMatcherProperties() override;

// Match interface

public:

  virtual void reset() override;
  QString name() const final;

// IBruteForceMatcher interface

public:

  virtual Norm normType() const override;
  virtual void setNormType(Norm normType) override;

private:

  Norm mNormType;

};

/*----------------------------------------------------------------*/

class FME_EXPORT BruteForceMatcher
  : public BruteForceMatcherProperties,
    public DescriptorMatcher
{

public:

  BruteForceMatcher();
  BruteForceMatcher(Norm normType);
  ~BruteForceMatcher() override {}

private:

  void update();

// DescriptorMatcher interface

public:

  std::vector<std::vector<cv::DMatch>> match(cv::InputArray &queryDescriptors,
                                       cv::InputArray &trainDescriptors,
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

class FME_EXPORT BruteForceMatcherCuda
  : public BruteForceMatcherProperties,
    public DescriptorMatcher
{

public:

  BruteForceMatcherCuda();
  BruteForceMatcherCuda(Norm normType);
  ~BruteForceMatcherCuda() override {}

private:

  void update();

// DescriptorMatcher interface

public:

  std::vector<std::vector<cv::DMatch>> match(cv::InputArray &queryDescriptors,
                                       cv::InputArray &trainDescriptors,
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


class FME_EXPORT IRobustMatcherRefinement
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

  IRobustMatcherRefinement() {}
  virtual ~IRobustMatcherRefinement() = default;

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
  virtual void reset() = 0;

};


/*----------------------------------------------------------------*/

class FME_EXPORT RobustMatcherProperties
  : public IRobustMatcherRefinement
{

public:

  RobustMatcherProperties();
  ~RobustMatcherProperties() override = default;

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
  void reset() override;

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

/*!
 * \brief Matching robusto
 *
 * Basado en:
 *
 * http://docs.opencv.org/3.1.0/dc/d2c/tutorial_real_time_pose.html
 */
class FME_EXPORT IRobustMatching
{

public:

  IRobustMatching() {}
  virtual ~IRobustMatching() = default;

public:

  /*!
   * \brief Establece el metodo de matching
   * \param[in] matcher
   */
  virtual void setDescriptorMatcher(const std::shared_ptr<DescriptorMatcher> &matcher) = 0;

  /*!
   * \brief Test de ratio
   * \param[in] matches
   */
  static std::vector<std::vector<cv::DMatch>>
  ratioTest(const std::vector<std::vector<cv::DMatch> > &matches, double ratio)
  {
    std::vector<std::vector<cv::DMatch>> goodMatches;

    for (size_t i = 0; i < matches.size(); i++){

      if (matches[i].size() > 1){
        // check distance ratio
        if (matches[i][0].distance / matches[i][1].distance <= static_cast<float>(ratio)) {
          goodMatches.push_back(matches[i]);
        }
      }

    }

    return goodMatches;
  }

  /*!
   * \brief test cruzado
   * Busqueda de matches simétricos
   * \param[in] matches1
   * \param[in] matches2
   * \param[out] symMatches
   */
  static std::vector<cv::DMatch> crossCheckTest(const std::vector<std::vector<cv::DMatch>> &matches1,
                                                const std::vector<std::vector<cv::DMatch>> &matches2)
  {
    std::vector<cv::DMatch> symMatches;

    for (size_t i = 0; i < matches1.size(); i++){

      if (matches1[i].empty() || matches1[i].size() < 2)
        continue;

      for (size_t j = 0; j < matches2.size(); j++){

        if (matches2[j].empty() || matches2[j].size() < 2)
          continue;

        if (matches1[i][0].queryIdx == matches2[j][0].trainIdx &&
            matches2[j][0].queryIdx == matches1[i][0].trainIdx) {
          symMatches.push_back(matches1[i][0]);
          break;
        }

      }

    }
    return symMatches;
  }

  virtual std::vector<cv::DMatch> geometricFilter(const std::vector<cv::DMatch> &matches,
                                                  const std::vector<cv::KeyPoint>& keypoints1,
                                                  const std::vector<cv::KeyPoint>& keypoints2) = 0;

  virtual std::vector<cv::DMatch> filterByHomographyMatrix(const std::vector<cv::DMatch> &matches,
                                                           const std::vector<cv::Point2f>& points1,
                                                           const std::vector<cv::Point2f>& points2) = 0;
  virtual std::vector<cv::DMatch> filterByEssentialMatrix(const std::vector<cv::DMatch> &matches,
                                                          const std::vector<cv::Point2f>& points1,
                                                          const std::vector<cv::Point2f>& points2) = 0;
  virtual std::vector<cv::DMatch> filterByFundamentalMatrix(const std::vector<cv::DMatch> &matches,
                                                            const std::vector<cv::Point2f>& points1,
                                                            const std::vector<cv::Point2f>& points2) = 0;

//  virtual std::vector<cv::DMatch> filterByHomographyMatrix(const std::vector<cv::DMatch> &matches,
//                                                           const std::vector<cv::KeyPoint>& keypoints1,
//                                                           const std::vector<cv::KeyPoint>& keypoints2,
//                                                           IRobustMatcherRefinement::HomographyComputeMethod method,
//                                                           double distance, int maxIters, double confidence) = 0;
//  virtual std::vector<cv::DMatch> filterByEssentialMatrix(const std::vector<cv::DMatch> &matches,
//                                                          const std::vector<cv::KeyPoint>& keypoints1,
//                                                          const std::vector<cv::KeyPoint>& keypoints2,
//                                                          IRobustMatcherRefinement::EssentialComputeMethod method) = 0;
//  virtual std::vector<cv::DMatch> filterByFundamentalMatrix(const std::vector<cv::DMatch> &matches,
//                                                            const std::vector<cv::KeyPoint>& keypoints1,
//                                                            const std::vector<cv::KeyPoint>& keypoints2,
//                                                            IRobustMatcherRefinement::FundamentalComputeMethod method,
//                                                            double confidence, double distance) = 0;

  virtual std::vector<cv::DMatch> match(const cv::Mat &queryDescriptor,
                                        const cv::Mat &trainDescriptor) = 0;

private:

  /*!
   * \brief Matching robusto
   * Hace un matching de caracteristicas usando los test de ratio y de simetría
   * \param[in] descriptor1
   * \param[in] descriptor2
   * \param[out] goodMatches
   */
  virtual std::vector<cv::DMatch> robustMatch(const cv::Mat &queryDescriptor,
                                              const cv::Mat &trainDescriptor) = 0;

  /*!
   * \brief Matching robusto
   * Hace un matching de caracteristicas usando el test de ratio
   * \param[in] descriptor1
   * \param[in] descriptor2
   * \param[out] pMatches
   */
  virtual std::vector<cv::DMatch> fastRobustMatch(const cv::Mat &queryDescriptor,
                                                  const cv::Mat &trainDescriptor) = 0;
};


/*----------------------------------------------------------------*/


class FME_EXPORT RobustMatching
  : public IRobustMatching,
    public RobustMatcherProperties
{

public:

  RobustMatching(const std::shared_ptr<DescriptorMatcher> &matcher);
  RobustMatching(const std::shared_ptr<DescriptorMatcher> &matcher,
                 double ratio,
                 bool crossCheck,
                 GeometricTest geometricTest,
                 HomographyComputeMethod homographyComputeMethod,
                 FundamentalComputeMethod fundamentalComputeMethod,
                 EssentialComputeMethod essentialComputeMethod,
                 double distance,
                 double confidence,
                 int maxIter);
  ~RobustMatching() override;

// IRobustMatching interface

public:

  void setDescriptorMatcher(const std::shared_ptr<DescriptorMatcher> &matcher) override;

  std::vector<cv::DMatch> match(const cv::Mat &queryDescriptor,
                                const cv::Mat &trainDescriptor) override;

//  std::vector<cv::DMatch> filterByHomographyMatrix(const std::vector<cv::DMatch> &matches,
//                                                   const std::vector<cv::KeyPoint>& keypoints1,
//                                                   const std::vector<cv::KeyPoint>& keypoints2,
//                                                   IRobustMatcherRefinement::HomographyComputeMethod method,
//                                                   double distance, int maxIters, double confidence) override;
//  std::vector<cv::DMatch> filterByEssentialMatrix(const std::vector<cv::DMatch> &matches,
//                                                  const std::vector<cv::KeyPoint>& keypoints1,
//                                                  const std::vector<cv::KeyPoint>& keypoints2,
//                                                  IRobustMatcherRefinement::EssentialComputeMethod method) override;
//  std::vector<cv::DMatch> filterByFundamentalMatrix(const std::vector<cv::DMatch> &matches,
//                                                    const std::vector<cv::KeyPoint>& keypoints1,
//                                                    const std::vector<cv::KeyPoint>& keypoints2,
//                                                    FundamentalComputeMethod method,
//                                                    double confidence = 0.99, double distance = 3.) override;

  std::vector<cv::DMatch> geometricFilter(const std::vector<cv::DMatch> &matches,
                                          const std::vector<cv::KeyPoint>& keypoints1,
                                          const std::vector<cv::KeyPoint>& keypoints2) override;

  std::vector<cv::DMatch> filterByHomographyMatrix(const std::vector<cv::DMatch> &matches,
                                                   const std::vector<cv::Point2f>& points1,
                                                   const std::vector<cv::Point2f>& points2) override;
  std::vector<cv::DMatch> filterByEssentialMatrix(const std::vector<cv::DMatch> &matches,
                                                  const std::vector<cv::Point2f>& points1,
                                                  const std::vector<cv::Point2f>& points2) override;
  std::vector<cv::DMatch> filterByFundamentalMatrix(const std::vector<cv::DMatch> &matches,
                                                    const std::vector<cv::Point2f>& points1,
                                                    const std::vector<cv::Point2f>& points2) override;

private:

  std::vector<cv::DMatch>  robustMatch(const cv::Mat &queryDescriptor,
                                       const cv::Mat &trainDescriptor) override;
  std::vector<cv::DMatch>  fastRobustMatch(const cv::Mat &queryDescriptor,
                                           const cv::Mat &trainDescriptor) override;

protected:

  std::shared_ptr<DescriptorMatcher> mMatcher;
};

/*----------------------------------------------------------------*/


FME_EXPORT void matchesWrite(const QString &fname, const std::vector<cv::DMatch> &matches);
FME_EXPORT void matchesRead(const QString &fname, std::vector<cv::DMatch> &matches);


/*----------------------------------------------------------------*/


} // namespace fme

Q_DECLARE_METATYPE(fme::IBruteForceMatcher::Norm)
Q_DECLARE_METATYPE(fme::IRobustMatcherRefinement::GeometricTest)
Q_DECLARE_METATYPE(fme::IRobustMatcherRefinement::HomographyComputeMethod)
Q_DECLARE_METATYPE(fme::IRobustMatcherRefinement::FundamentalComputeMethod)
Q_DECLARE_METATYPE(fme::IRobustMatcherRefinement::EssentialComputeMethod)

#endif // FME_MATCHER_H
