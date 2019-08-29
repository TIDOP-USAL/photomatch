#ifndef FME_MATCHER_H
#define FME_MATCHER_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{

class FME_EXPORT IDescriptorMatcher
{

public:

  IDescriptorMatcher() {}
  virtual ~IDescriptorMatcher() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  /*!
   * \brief matchingMethod
   * \return
   */
  virtual QString matchingMethod() const = 0;

  /*!
   * \brief One of NORM_L1, NORM_L2, NORM_HAMMING, NORM_HAMMING2.
   * \return
   */
  virtual QString normType() const = 0;

  /*!
   * \brief ratio
   * \return
   */
  virtual double ratio() const = 0;

  /*!
   * \brief distance
   * \return
   */
  virtual double distance() const = 0;

  /*!
   * \brief confidence
   * \return
   */
  virtual double confidence() const = 0;

  /*!
   * \brief crossMatching
   * \return
   */
  virtual bool crossMatching() const = 0;

  /*!
   * \brief setMatchingMethod
   * \param matchingMethod
   */
  virtual void setMatchingMethod(const QString &matchingMethod) = 0;

  /*!
   * \brief setNormType
   * \param[in] normType
   */
  virtual void setNormType(const QString &normType) = 0;

  /*!
   * \brief setRatio
   * \param[in] ratio
   */
  virtual void setRatio(double ratio) = 0;

  /*!
   * \brief setDistance
   * \param[in] distance
   */
  virtual void setDistance(double distance) = 0;

  /*!
   * \brief setConfidence
   * \param[in] confidence
   */
  virtual void setConfidence(double confidence) = 0;

  /*!
   * \brief setCrossMatching
   * \param[in] crossMatching
   */
  virtual void setCrossMatching(bool crossMatching) = 0;

};

class FME_EXPORT DescriptorMatcherProperties
  : public IDescriptorMatcher
{

public:

  DescriptorMatcherProperties();
  ~DescriptorMatcherProperties() override;

// IDescriptorMatcher interface

public:


  QString matchingMethod() const override;
  QString normType() const override;
  double ratio() const override;
  double distance() const override;
  double confidence() const override;
  bool crossMatching() const override;
  void setMatchingMethod(const QString &matchingMethod) override;
  void setNormType(const QString &normType) override;
  void setRatio(double ratio) override;
  void setDistance(double distance) override;
  void setConfidence(double confidence) override;
  void setCrossMatching(bool crossMatching) override;

  void reset() override;

protected:

  QString mMatchingMethod;
  QString mNorm;
  double mRatio;
  double mDistance;
  double mConfidence;
  bool mCrossMatching;

};

//class FME_EXPORT BruteForceMatcherProperties
//  : public IBruteForceMatcher
//{

//public:

//  BruteForceMatcherProperties();
//  ~BruteForceMatcherProperties() override;

//// Match interface

//public:

//  virtual void reset() override;

//// IBruteForceMatcher interface

//public:

//  virtual Norm normType() const override;
//  virtual void setNormType(Norm normType) override;

//private:

//  Norm mNormType;

//};


///*----------------------------------------------------------------*/


//class FME_EXPORT BruteForceMatcher
//  : public BruteForceMatcherProperties,
//    public DescriptorMatcher
//{

//public:

//  BruteForceMatcher();
//  BruteForceMatcher(Norm normType);
//  ~BruteForceMatcher() override {}

//private:

//  void update();

//// DescriptorMatcher interface

//public:

//  void match(cv::InputArray &queryDescriptors, cv::InputArray &trainDescriptors, std::vector<cv::DMatch> &matches, cv::InputArray mask) override;

//// Match interface

//public:

//  void reset() override;

//// IBruteForceMatcher interface

//public:

//  void setNormType(Norm normType) override;

//protected:

//  cv::Ptr<cv::BFMatcher> mBFMatcher;
//};

///*----------------------------------------------------------------*/


//class FME_EXPORT FlannMatcherProperties
//  : public IFlannMatcher
//{

//public:

//  FlannMatcherProperties();
//  ~FlannMatcherProperties() override;

//// Match interface

//public:

//  virtual void reset() override;

//};

///*----------------------------------------------------------------*/


//class FME_EXPORT FlannMatcher
//  : public FlannMatcherProperties,
//    public DescriptorMatcher
//{

//public:

//  FlannMatcher();
//  ~FlannMatcher() override;

//// DescriptorMatcher interface

//public:

//  void match(cv::InputArray &queryDescriptors, cv::InputArray &trainDescriptors, std::vector<cv::DMatch> &matches, cv::InputArray mask) override;

//// Match interface

//public:

//  void reset() override;

//protected:

//  cv::Ptr<cv::FlannBasedMatcher> mFlannBasedMatcher;

//};

} // namespace fme


#endif // FME_MATCHER_H
