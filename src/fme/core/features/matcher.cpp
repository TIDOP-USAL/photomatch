#include "matcher.h"

#include <opencv2/xfeatures2d.hpp>

namespace fme
{

DescriptorMatcherProperties::DescriptorMatcherProperties()
  : IDescriptorMatcher(),
    mMatchingMethod("BRUTE_FORCE"),
    mNorm("NORM_L2"),
    mRatio(0.8),
    mDistance(0.7),
    mConfidence(0.999),
    mCrossMatching(true)
{

}

DescriptorMatcherProperties::~DescriptorMatcherProperties()
{

}

QString DescriptorMatcherProperties::matchingMethod() const
{
  return mMatchingMethod;
}

QString DescriptorMatcherProperties::normType() const
{
  return mNorm;
}

double DescriptorMatcherProperties::ratio() const
{
  return mRatio;
}

double DescriptorMatcherProperties::distance() const
{
  return mDistance;
}

double DescriptorMatcherProperties::confidence() const
{
  return mConfidence;
}

bool DescriptorMatcherProperties::crossMatching() const
{
  return mCrossMatching;
}

void DescriptorMatcherProperties::setMatchingMethod(const QString &matchingMethod)
{
  mMatchingMethod = matchingMethod;
}

void DescriptorMatcherProperties::setNormType(const QString &normType)
{
  mNorm = normType;
}

void DescriptorMatcherProperties::setRatio(double ratio)
{
  mRatio = ratio;
}

void DescriptorMatcherProperties::setDistance(double distance)
{
  mDistance = distance;
}

void DescriptorMatcherProperties::setConfidence(double confidence)
{
  mConfidence = confidence;
}

void DescriptorMatcherProperties::setCrossMatching(bool crossMatching)
{
  mCrossMatching = crossMatching;
}

void DescriptorMatcherProperties::reset()
{
  mMatchingMethod = "Brute-Force";
  mNorm = "NORM_L2";
  mRatio = 0.8;
  mDistance = 0.7;
  mConfidence = 0.999;
  mCrossMatching = true;
}

//BruteForceMatcherProperties::BruteForceMatcherProperties()
//  : IBruteForceMatcher(),
//    mNormType(BruteForceMatcherProperties::Norm::l2)
//{

//}

//BruteForceMatcherProperties::~BruteForceMatcherProperties()
//{

//}

//void BruteForceMatcherProperties::reset()
//{
//  mNormType = BruteForceMatcherProperties::Norm::l2;
//}

//BruteForceMatcherProperties::Norm BruteForceMatcherProperties::normType() const
//{
//  return mNormType;
//}

//void BruteForceMatcherProperties::setNormType(Norm normType)
//{
//  mNormType = normType;
//}

///*----------------------------------------------------------------*/


//BruteForceMatcher::BruteForceMatcher()
//  : BruteForceMatcherProperties(),
//    DescriptorMatcher()
//{
//  update();
//}


//BruteForceMatcher::BruteForceMatcher(IBruteForceMatcher::Norm normType)
//  : BruteForceMatcherProperties(),
//    DescriptorMatcher()
//{
//  BruteForceMatcherProperties::setNormType(normType);
//  update();
//}

//void BruteForceMatcher::update()
//{
//  int norm = cv::NORM_L2;
//  BruteForceMatcherProperties::Norm norm_type = BruteForceMatcherProperties::normType();
//  if (norm_type == BruteForceMatcherProperties::Norm::l1) {
//    norm = cv::NORM_L1;
//  } else if (norm_type == BruteForceMatcherProperties::Norm::l2) {
//    norm = cv::NORM_L2;
//  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming) {
//    norm = cv::NORM_HAMMING;
//  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming2) {
//    norm = cv::NORM_HAMMING2;
//  }

//  mBFMatcher = cv::BFMatcher::create(norm);
//}

//void BruteForceMatcher::match(cv::InputArray &queryDescriptors,
//                                 cv::InputArray &trainDescriptors,
//                                 std::vector<cv::DMatch> &matches,
//                                 cv::InputArray mask)
//{
//  //mBFMatcher->knnMatch(queryDescriptors, trainDescriptors, matches, 2, mask);
//  mBFMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
//}

//void BruteForceMatcher::reset()
//{
//  BruteForceMatcherProperties::reset();
//  update();
//}

//void BruteForceMatcher::setNormType(IBruteForceMatcher::Norm normType)
//{
//  BruteForceMatcherProperties::setNormType(normType);
//}

///*----------------------------------------------------------------*/

//FlannMatcherProperties::FlannMatcherProperties()
//  : IFlannMatcher()
//{
//}

//FlannMatcherProperties::~FlannMatcherProperties()
//{
//}

//void FlannMatcherProperties::reset()
//{
//}

///*----------------------------------------------------------------*/

//FlannMatcher::FlannMatcher()
//  : FlannMatcherProperties(),
//    DescriptorMatcher()
//{
//  mFlannBasedMatcher = cv::FlannBasedMatcher::create();
//}

//FlannMatcher::~FlannMatcher()
//{

//}

//void FlannMatcher::match(cv::InputArray &queryDescriptors, cv::InputArray &trainDescriptors, std::vector<cv::DMatch> &matches, cv::InputArray mask)
//{
//  mFlannBasedMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
//}

//void FlannMatcher::reset()
//{
//  mFlannBasedMatcher = cv::FlannBasedMatcher::create();
//}


} // namespace fme







