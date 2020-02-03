#include "matcher.h"

#include <tidop/core/messages.h>

#include <opencv2/xfeatures2d.hpp>
#include <opencv2/calib3d.hpp>

#include <QFileInfo>

namespace photomatch
{


FlannMatcherProperties::FlannMatcherProperties()
  : IFlannMatcher(),
    mIndex(FlannMatcherProperties::Index::kdtree)
{
}

FlannMatcherProperties::~FlannMatcherProperties()
{
}

void FlannMatcherProperties::reset()
{
  mIndex = FlannMatcherProperties::Index::kdtree;
}

QString FlannMatcherProperties::name() const
{
  return QString("Flann Based Matching");
}

IFlannMatcher::Index FlannMatcherProperties::index() const
{
  return mIndex;
}

void FlannMatcherProperties::setIndex(IFlannMatcher::Index index)
{
  mIndex = index;
}

/*----------------------------------------------------------------*/


FlannMatcher::FlannMatcher()
  : FlannMatcherProperties(),
    DescriptorMatcher()
{
  update();
}

FlannMatcher::FlannMatcher(Index index)
  : FlannMatcherProperties(),
    DescriptorMatcher()
{
  FlannMatcherProperties::setIndex(index);
  update();
}

FlannMatcher::~FlannMatcher()
{

}

void FlannMatcher::update()
{
  cv::Ptr<cv::flann::IndexParams> indexParams;
  if (FlannMatcherProperties::index() == FlannMatcherProperties::Index::kdtree){
    indexParams = cv::makePtr<cv::flann::KDTreeIndexParams>();
  } else if (FlannMatcherProperties::index() == FlannMatcherProperties::Index::lsh){
    indexParams = cv::makePtr<cv::flann::LshIndexParams>(12, 20, 2);
  }
  mFlannBasedMatcher = cv::Ptr<cv::FlannBasedMatcher>(new cv::FlannBasedMatcher(indexParams));
}

bool FlannMatcher::match(cv::InputArray &queryDescriptors,
                         cv::InputArray &trainDescriptors,
                         std::vector<cv::DMatch> &matches,
                         cv::InputArray mask)
{
  try {
    mFlannBasedMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
  } catch (cv::Exception &e) {
    msgError("Flann Based Matcher error: %s", e.what());
    return true;
  }
  return false;
}

bool FlannMatcher::match(cv::InputArray &queryDescriptors,
                         cv::InputArray &trainDescriptors,
                         std::vector<std::vector<cv::DMatch>> &matches,
                         cv::InputArray mask)
{
  try {
    mFlannBasedMatcher->knnMatch(queryDescriptors, trainDescriptors, matches, 2, mask);
  } catch (cv::Exception &e) {
    msgError("Flann Based Matcher error: %s", e.what());
    return true;
  }
  return false;
}

void FlannMatcher::reset()
{
  FlannMatcherProperties::reset();
  update();
}

void FlannMatcher::setIndex(IFlannMatcher::Index index)
{
}

/*----------------------------------------------------------------*/



BruteForceMatcherProperties::BruteForceMatcherProperties()
  : IBruteForceMatcher(),
    mNormType(BruteForceMatcherProperties::Norm::l2)
{
}

BruteForceMatcherProperties::~BruteForceMatcherProperties()
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

void BruteForceMatcherProperties::setNormType(IBruteForceMatcher::Norm normType)
{
  mNormType = normType;
}

/*----------------------------------------------------------------*/


BruteForceMatcher::BruteForceMatcher()
  : BruteForceMatcherProperties(),
    DescriptorMatcher()
{
  update();
}

BruteForceMatcher::BruteForceMatcher(IBruteForceMatcher::Norm normType)
  : BruteForceMatcherProperties(),
    DescriptorMatcher()
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

void BruteForceMatcher::update()
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

  mBFMatcher = cv::BFMatcher::create(norm);
}

bool BruteForceMatcher::match(cv::InputArray &queryDescriptors,
                              cv::InputArray &trainDescriptors,
                              std::vector<cv::DMatch> &matches,
                              cv::InputArray mask)
{
  try {
    mBFMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
    return true;
  }
  return false;
}

bool BruteForceMatcher::match(cv::InputArray &queryDescriptors,
                              cv::InputArray &trainDescriptors,
                              std::vector<std::vector<cv::DMatch>> &matches,
                              cv::InputArray mask)
{
  try {
    mBFMatcher->knnMatch(queryDescriptors, trainDescriptors, matches, 2, mask);
  } catch (cv::Exception &e) {
    msgError("Brute-force Matcher error: %s", e.what());
    return true;
  }
  return false;
}

void BruteForceMatcher::reset()
{
  BruteForceMatcherProperties::reset();
  update();
}

void BruteForceMatcher::setNormType(IBruteForceMatcher::Norm normType)
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

/*----------------------------------------------------------------*/

#ifdef HAVE_CUDA

BruteForceMatcherCuda::BruteForceMatcherCuda()
  : BruteForceMatcherProperties(),
    DescriptorMatcher()
{
  update();
}

BruteForceMatcherCuda::BruteForceMatcherCuda(IBruteForceMatcher::Norm normType)
  : BruteForceMatcherProperties(),
    DescriptorMatcher()
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
  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming2) {
    norm = cv::NORM_HAMMING2;
  }

  mBFMatcher = cv::cuda::DescriptorMatcher::createBFMatcher(norm);
}

bool BruteForceMatcherCuda::match(cv::InputArray &queryDescriptors,
                                  cv::InputArray &trainDescriptors,
                                  std::vector<cv::DMatch> &matches,
                                  cv::InputArray mask)
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

bool BruteForceMatcherCuda::match(cv::InputArray &queryDescriptors,
                                  cv::InputArray &trainDescriptors,
                                  std::vector<std::vector<cv::DMatch>> &matches,
                                  cv::InputArray mask)
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

void BruteForceMatcherCuda::setNormType(IBruteForceMatcher::Norm normType)
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

#endif // HAVE_CUDA

/*----------------------------------------------------------------*/

RobustMatchingProperties::RobustMatchingProperties()
  : IRobustMatcherRefinement(),
    mRatio(0.8),
    mCrossCheck(true),
    mGeometricTest(GeometricTest::fundamental),
    mHomographyComputeMethod(HomographyComputeMethod::ransac),
    mFundamentalComputeMethod(FundamentalComputeMethod::ransac),
    mEssentialComputeMethod(EssentialComputeMethod::ransac),
    mDistance(0.7),
    mConfidence(0.999),
    mMaxIters(2000)
{
}

double RobustMatchingProperties::ratio() const
{
  return mRatio;
}

void RobustMatchingProperties::setRatio(double ratio)
{
  mRatio = ratio;
}

bool RobustMatchingProperties::crossCheck() const
{
  return mCrossCheck;
}

void RobustMatchingProperties::setCrossCheck(bool crossCheck)
{
  mCrossCheck = crossCheck;
}

IRobustMatcherRefinement::GeometricTest RobustMatchingProperties::geometricTest() const
{
  return mGeometricTest;
}

void RobustMatchingProperties::setGeometricTest(IRobustMatcherRefinement::GeometricTest geometricTest)
{
  mGeometricTest = geometricTest;
}

IRobustMatcherRefinement::HomographyComputeMethod RobustMatchingProperties::homographyComputeMethod() const
{
  return mHomographyComputeMethod;
}

void RobustMatchingProperties::setHomographyComputeMethod(IRobustMatcherRefinement::HomographyComputeMethod computeMethod)
{
  mHomographyComputeMethod = computeMethod;
}

IRobustMatcherRefinement::FundamentalComputeMethod RobustMatchingProperties::fundamentalComputeMethod() const
{
  return mFundamentalComputeMethod;
}

void RobustMatchingProperties::setFundamentalComputeMethod(IRobustMatcherRefinement::FundamentalComputeMethod computeMethod)
{
  mFundamentalComputeMethod = computeMethod;
}

IRobustMatcherRefinement::EssentialComputeMethod RobustMatchingProperties::essentialComputeMethod() const
{
  return mEssentialComputeMethod;
}

void RobustMatchingProperties::setEssentialComputeMethod(IRobustMatcherRefinement::EssentialComputeMethod computeMethod)
{
  mEssentialComputeMethod = computeMethod;
}

double RobustMatchingProperties::distance() const
{
  return mDistance;
}

void RobustMatchingProperties::setDistance(double distance)
{
  mDistance = distance;
}

double RobustMatchingProperties::confidence() const
{
  return mConfidence;
}

void RobustMatchingProperties::setConfidence(double confidence)
{
  mConfidence = confidence;
}

int RobustMatchingProperties::maxIter() const
{
  return mMaxIters;
}

void RobustMatchingProperties::setMaxIters(int maxIter)
{
  mMaxIters = maxIter;
}

void RobustMatchingProperties::reset()
{
  mRatio = 0.8;
  mCrossCheck = true;
  mGeometricTest = GeometricTest::fundamental;
  mHomographyComputeMethod = HomographyComputeMethod::ransac;
  mFundamentalComputeMethod = FundamentalComputeMethod::ransac;
  mEssentialComputeMethod = EssentialComputeMethod::ransac;
  mDistance = 0.7;
  mConfidence = 0.999;
  mMaxIters = 2000;
}

QString photomatch::RobustMatchingProperties::name() const
{
  return QString("Robust Matcher");
}

/*----------------------------------------------------------------*/


//RobustMatching::RobustMatching(const std::shared_ptr<DescriptorMatcher> &matcher)
//  : IRobustMatching(),
//    RobustMatchingProperties(),
//    mMatcher(matcher)
//{
//}

//RobustMatching::RobustMatching(const std::shared_ptr<DescriptorMatcher> &matcher,
//                               double ratio,
//                               bool crossCheck,
//                               GeometricTest geometricTest,
//                               HomographyComputeMethod homographyComputeMethod,
//                               FundamentalComputeMethod fundamentalComputeMethod,
//                               EssentialComputeMethod essentialComputeMethod,
//                               double distance,
//                               double confidence,
//                               int maxIter)
//  : IRobustMatching(),
//    RobustMatchingProperties(),
//    mMatcher(matcher)
//{
//  this->setRatio(ratio);
//  this->setCrossCheck(crossCheck);
//  this->setGeometricTest(geometricTest);
//  this->setHomographyComputeMethod(homographyComputeMethod);
//  this->setFundamentalComputeMethod(fundamentalComputeMethod);
//  this->setEssentialComputeMethod(essentialComputeMethod);
//  this->setDistance(distance);
//  this->setConfidence(confidence);
//  this->setMaxIters(maxIter);
//}

//RobustMatching::~RobustMatching()
//{
//}

//void RobustMatching::setDescriptorMatcher(const std::shared_ptr<DescriptorMatcher> &matcher)
//{
//  mMatcher = matcher;
//}

//std::vector<cv::DMatch> RobustMatching::match(const cv::Mat &queryDescriptor,
//                                              const cv::Mat &trainDescriptor,
//                                              std::vector<cv::DMatch> *wrongMatches)
//{
//  if (this->crossCheck()){
//    return this->robustMatch(queryDescriptor, trainDescriptor, wrongMatches);
//  } else {
//    return this->fastRobustMatch(queryDescriptor, trainDescriptor, wrongMatches);
//  }
//}

//std::vector<cv::DMatch> RobustMatching::geometricFilter(const std::vector<cv::DMatch> &matches,
//                                                        const std::vector<cv::KeyPoint> &keypoints1,
//                                                        const std::vector<cv::KeyPoint> &keypoints2,
//                                                        std::vector<cv::DMatch> *wrongMatches)
//{
//  std::vector<cv::DMatch> filter_matches;

//  // Convert keypoints into Point2f
//  size_t nPoints = matches.size();
//  std::vector<cv::Point2f> pts1(nPoints);
//  std::vector<cv::Point2f> pts2(nPoints);
//  for (size_t igm = 0; igm < nPoints; igm++) {
//    pts1[igm] = keypoints1[static_cast<size_t>(matches[igm].queryIdx)].pt;
//    pts2[igm] = keypoints2[static_cast<size_t>(matches[igm].trainIdx)].pt;
//  }

//  IRobustMatcherRefinement::GeometricTest geometric_test = RobustMatchingProperties::geometricTest();
//  if (geometric_test == IRobustMatcherRefinement::GeometricTest::essential) {


//  } else if (geometric_test == IRobustMatcherRefinement::GeometricTest::homography){

//    filter_matches = filterByHomographyMatrix(matches, pts1, pts2, wrongMatches);

//  } else if (geometric_test == IRobustMatcherRefinement::GeometricTest::fundamental){

//    filter_matches = filterByFundamentalMatrix(matches, pts1, pts2, wrongMatches);

//  }

//  return filter_matches;
//}

//std::vector<cv::DMatch> RobustMatching::filterByHomographyMatrix(const std::vector<cv::DMatch> &matches,
//                                                                 const std::vector<cv::Point2f> &points1,
//                                                                 const std::vector<cv::Point2f> &points2,
//                                                                 std::vector<cv::DMatch> *wrongMatches)
//{
//  std::vector<cv::DMatch> filter_matches;

//  int hcm = cv::RANSAC;
//  IRobustMatcherRefinement::HomographyComputeMethod homographyComputeMethod = this->homographyComputeMethod();
//  if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::all_points){
//    hcm = 0;
//  } else if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::ransac){
//    hcm = cv::RANSAC;
//  } else if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::lmeds){
//    hcm = cv::LMEDS;
//  } else if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::rho){
//    hcm = cv::RHO;
//  }

//  size_t nPoints = matches.size();
//  std::vector<uchar> inliers(nPoints, 0);
//  cv::Mat H = cv::findHomography(cv::Mat(points1), cv::Mat(points2), hcm, this->distance(), inliers, this->maxIter(), this->confidence());

//  // extract the surviving (inliers) matches
//  std::vector<uchar>::const_iterator itIn = inliers.begin();
//  std::vector<cv::DMatch>::const_iterator itM = matches.begin();
//  // for all matches
//  for (; itIn != inliers.end(); ++itIn, ++itM) {

//    if (*itIn) {
//      filter_matches.push_back(*itM);
//    } else {
//      if (wrongMatches) wrongMatches->push_back(*itM);
//    }
//  }


//  return filter_matches;
//}

//std::vector<cv::DMatch> RobustMatching::filterByEssentialMatrix(const std::vector<cv::DMatch> &matches,
//                                                                const std::vector<cv::Point2f> &points1,
//                                                                const std::vector<cv::Point2f> &points2,
//                                                                std::vector<cv::DMatch> *wrongMatches)
//{
//  std::vector<cv::DMatch> filter_matches;

//  int fm = cv::RANSAC;
//  IRobustMatcherRefinement::EssentialComputeMethod essentialComputeMethod = this->essentialComputeMethod();
//  if (essentialComputeMethod == IRobustMatcherRefinement::EssentialComputeMethod::ransac){
//    fm = cv::RANSAC;
//  } else if (essentialComputeMethod == IRobustMatcherRefinement::EssentialComputeMethod::lmeds){
//    fm = cv::LMEDS;
//  }

//  // Convert keypoints into Point2f
//  size_t nPoints = matches.size();

//  TL_TODO("Se necesita la calibración de la cámara (focal y pp) con lo cual no se si es interesante")

////  std::vector<uchar> inliers(nPoints, 0);
////  cv::findEssentialMat(	InputArray 	points1,
////  InputArray 	points2,
////  InputArray 	cameraMatrix,
////  int 	method = RANSAC,
////  double 	prob = 0.999,
////  double 	threshold = 1.0,
////  OutputArray 	mask = noArray()
////  )

//  return filter_matches;
//}

//std::vector<cv::DMatch> RobustMatching::filterByFundamentalMatrix(const std::vector<cv::DMatch> &matches,
//                                                                  const std::vector<cv::Point2f> &points1,
//                                                                  const std::vector<cv::Point2f> &points2,
//                                                                  std::vector<cv::DMatch> *wrongMatches)
//{
//  int fm_method = cv::FM_RANSAC;
//  IRobustMatcherRefinement::FundamentalComputeMethod fundamentalComputeMethod = this->fundamentalComputeMethod();
//  if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_7_point){
//    fm_method = cv::FM_7POINT;
//  } else if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_8_point){
//    fm_method = cv::FM_8POINT;
//  } else if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::ransac){
//    fm_method = cv::FM_RANSAC;
//  } else if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::lmeds){
//    fm_method = cv::FM_LMEDS;
//  }

//  // Convert keypoints into Point2f
//  size_t nPoints = matches.size();
//  std::vector<uchar> inliers(nPoints, 0);
//  cv::Mat fundamental = cv::findFundamentalMat(cv::Mat(points1), cv::Mat(points2), inliers,
//                                               fm_method, this->distance(), this->confidence());

//  std::vector<cv::DMatch> filter_matches;
//  // extract the surviving (inliers) matches
//  std::vector<uchar>::const_iterator itIn = inliers.begin();
//  std::vector<cv::DMatch>::const_iterator itM = matches.begin();
//  // for all matches
//  for (; itIn != inliers.end(); ++itIn, ++itM) {

//    if (*itIn) { // it is a valid match
//      filter_matches.push_back(*itM);
//    } else {
//      if (wrongMatches) wrongMatches->push_back(*itM);
//    }
//  }

//  return filter_matches;
//}

//std::vector<cv::DMatch> RobustMatching::robustMatch(const cv::Mat &queryDescriptor,
//                                                    const cv::Mat &trainDescriptor,
//                                                    std::vector<cv::DMatch> *wrongMatches)
//{

//  std::vector<cv::DMatch> goodMatches;

//  std::vector<std::vector<cv::DMatch>> matches12;
//  std::vector<std::vector<cv::DMatch>> matches21;

//  bool err = mMatcher->match(queryDescriptor, trainDescriptor, matches12);
//  if (err) return goodMatches;

//  err = mMatcher->match(trainDescriptor, queryDescriptor, matches21);
//  if (err) return goodMatches;

//  std::vector<std::vector<cv::DMatch>> wrong_matches12;
//  std::vector<std::vector<cv::DMatch>> wrong_matches21;
//  std::vector<std::vector<cv::DMatch>> good_matches12 = this->ratioTest(matches12, this->ratio(), &wrong_matches12);
//  std::vector<std::vector<cv::DMatch>> good_matches21 = this->ratioTest(matches21, this->ratio(), &wrong_matches21);

//  matches12.clear();
//  matches21.clear();

//  if (wrongMatches){
//    for (size_t i = 0; i < wrong_matches12.size(); i++){
//      wrongMatches->push_back(wrong_matches12[i][0]);
//    }
//  }


//  goodMatches = this->crossCheckTest(good_matches12, good_matches21, wrongMatches);

//  return goodMatches;
//}

//std::vector<cv::DMatch> RobustMatching::fastRobustMatch(const cv::Mat &queryDescriptor,
//                                                        const cv::Mat &trainDescriptor,
//                                                        std::vector<cv::DMatch> *wrongMatches)
//{
//  std::vector<cv::DMatch> goodMatches;

//  std::vector<std::vector<cv::DMatch>> matches;
//  bool err = mMatcher->match(queryDescriptor, trainDescriptor, matches);
//  if (err) return goodMatches;

//  std::vector<std::vector<cv::DMatch>> ratio_test_wrong_matches;
//  std::vector<std::vector<cv::DMatch>> ratio_test_matches = this->ratioTest(matches, this->ratio(), &ratio_test_wrong_matches);

//  for (auto &match : ratio_test_matches){
//    goodMatches.push_back(match[0]);
//  }

//  if (wrongMatches) {
//    for (auto &wrong_match : ratio_test_wrong_matches){
//      wrongMatches->push_back(wrong_match[0]);
//    }
//  }

//  return goodMatches;

//}

/*----------------------------------------------------------------*/


RobustMatchingStrategy::RobustMatchingStrategy(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher)
  : RobustMatchingProperties(),
    MatchingAlgorithm(),
    mDescriptorMatcher(descriptorMatcher)
{

}

RobustMatchingStrategy::RobustMatchingStrategy(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher,
                                               double ratio,
                                               bool crossCheck,
                                               GeometricTest geometricTest,
                                               HomographyComputeMethod homographyComputeMethod,
                                               FundamentalComputeMethod fundamentalComputeMethod,
                                               EssentialComputeMethod essentialComputeMethod,
                                               double distance,
                                               double confidence,
                                               int maxIter)
  : RobustMatchingProperties(),
    MatchingAlgorithm(),
    mDescriptorMatcher(descriptorMatcher)
{
  this->setRatio(ratio);
  this->setCrossCheck(crossCheck);
  this->setGeometricTest(geometricTest);
  this->setHomographyComputeMethod(homographyComputeMethod);
  this->setFundamentalComputeMethod(fundamentalComputeMethod);
  this->setEssentialComputeMethod(essentialComputeMethod);
  this->setDistance(distance);
  this->setConfidence(confidence);
  this->setMaxIters(maxIter);
}

RobustMatchingStrategy::~RobustMatchingStrategy()
{

}

void RobustMatchingStrategy::setDescriptorMatcher(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher)
{
  mDescriptorMatcher = descriptorMatcher;
}

std::vector<cv::DMatch> RobustMatchingStrategy::geometricFilter(const std::vector<cv::DMatch> &matches, const std::vector<cv::KeyPoint> &keypoints1, const std::vector<cv::KeyPoint> &keypoints2, std::vector<cv::DMatch> *wrongMatches)
{
  std::vector<cv::DMatch> filter_matches;

  // Convert keypoints into Point2f
  size_t nPoints = matches.size();
  std::vector<cv::Point2f> pts1(nPoints);
  std::vector<cv::Point2f> pts2(nPoints);
  for (size_t igm = 0; igm < nPoints; igm++) {
    pts1[igm] = keypoints1[static_cast<size_t>(matches[igm].queryIdx)].pt;
    pts2[igm] = keypoints2[static_cast<size_t>(matches[igm].trainIdx)].pt;
  }

  IRobustMatcherRefinement::GeometricTest geometric_test = RobustMatchingProperties::geometricTest();
  if (geometric_test == IRobustMatcherRefinement::GeometricTest::essential) {


  } else if (geometric_test == IRobustMatcherRefinement::GeometricTest::homography){

    filter_matches = filterByHomographyMatrix(matches, pts1, pts2, wrongMatches);

  } else if (geometric_test == IRobustMatcherRefinement::GeometricTest::fundamental){

    filter_matches = filterByFundamentalMatrix(matches, pts1, pts2, wrongMatches);

  }

  return filter_matches;
}

std::vector<cv::DMatch> RobustMatchingStrategy::filterByHomographyMatrix(const std::vector<cv::DMatch> &matches, const std::vector<cv::Point2f> &points1, const std::vector<cv::Point2f> &points2, std::vector<cv::DMatch> *wrongMatches)
{
  std::vector<cv::DMatch> filter_matches;

  int hcm = cv::RANSAC;
  IRobustMatcherRefinement::HomographyComputeMethod homographyComputeMethod = this->homographyComputeMethod();
  if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::all_points){
    hcm = 0;
  } else if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::ransac){
    hcm = cv::RANSAC;
  } else if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::lmeds){
    hcm = cv::LMEDS;
  } else if (homographyComputeMethod == IRobustMatcherRefinement::HomographyComputeMethod::rho){
    hcm = cv::RHO;
  }

  size_t nPoints = matches.size();
  std::vector<uchar> inliers(nPoints, 0);
  cv::Mat H = cv::findHomography(cv::Mat(points1), cv::Mat(points2), hcm, this->distance(), inliers, this->maxIter(), this->confidence());

  // extract the surviving (inliers) matches
  std::vector<uchar>::const_iterator itIn = inliers.begin();
  std::vector<cv::DMatch>::const_iterator itM = matches.begin();
  // for all matches
  for (; itIn != inliers.end(); ++itIn, ++itM) {

    if (*itIn) {
      filter_matches.push_back(*itM);
    } else {
      if (wrongMatches) wrongMatches->push_back(*itM);
    }
  }


  return filter_matches;
}

std::vector<cv::DMatch> RobustMatchingStrategy::filterByEssentialMatrix(const std::vector<cv::DMatch> &matches, const std::vector<cv::Point2f> &points1, const std::vector<cv::Point2f> &points2, std::vector<cv::DMatch> *wrongMatches)
{
  std::vector<cv::DMatch> filter_matches;

  int fm = cv::RANSAC;
  IRobustMatcherRefinement::EssentialComputeMethod essentialComputeMethod = this->essentialComputeMethod();
  if (essentialComputeMethod == IRobustMatcherRefinement::EssentialComputeMethod::ransac){
    fm = cv::RANSAC;
  } else if (essentialComputeMethod == IRobustMatcherRefinement::EssentialComputeMethod::lmeds){
    fm = cv::LMEDS;
  }

  // Convert keypoints into Point2f
  size_t nPoints = matches.size();

  TL_TODO("Se necesita la calibración de la cámara (focal y pp) con lo cual no se si es interesante")

//  std::vector<uchar> inliers(nPoints, 0);
//  cv::findEssentialMat(	InputArray 	points1,
//  InputArray 	points2,
//  InputArray 	cameraMatrix,
//  int 	method = RANSAC,
//  double 	prob = 0.999,
//  double 	threshold = 1.0,
//  OutputArray 	mask = noArray()
//  )

      return filter_matches;
}

std::vector<cv::DMatch> RobustMatchingStrategy::filterByFundamentalMatrix(const std::vector<cv::DMatch> &matches, const std::vector<cv::Point2f> &points1, const std::vector<cv::Point2f> &points2, std::vector<cv::DMatch> *wrongMatches)
{
  int fm_method = cv::FM_RANSAC;
  IRobustMatcherRefinement::FundamentalComputeMethod fundamentalComputeMethod = this->fundamentalComputeMethod();
  if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_7_point){
    fm_method = cv::FM_7POINT;
  } else if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_8_point){
    fm_method = cv::FM_8POINT;
  } else if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::ransac){
    fm_method = cv::FM_RANSAC;
  } else if (fundamentalComputeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::lmeds){
    fm_method = cv::FM_LMEDS;
  }

  // Convert keypoints into Point2f
  size_t nPoints = matches.size();
  std::vector<uchar> inliers(nPoints, 0);
  cv::Mat fundamental = cv::findFundamentalMat(cv::Mat(points1), cv::Mat(points2), inliers,
                                               fm_method, this->distance(), this->confidence());

  std::vector<cv::DMatch> filter_matches;
  // extract the surviving (inliers) matches
  std::vector<uchar>::const_iterator itIn = inliers.begin();
  std::vector<cv::DMatch>::const_iterator itM = matches.begin();
  // for all matches
  for (; itIn != inliers.end(); ++itIn, ++itM) {

    if (*itIn) { // it is a valid match
      filter_matches.push_back(*itM);
    } else {
      if (wrongMatches) wrongMatches->push_back(*itM);
    }
  }

  return filter_matches;
}

std::vector<cv::DMatch> RobustMatchingStrategy::match(const cv::Mat &queryDescriptor, const cv::Mat &trainDescriptor, std::vector<cv::DMatch> *wrongMatches)
{
  if (this->crossCheck()){
    return this->robustMatch(queryDescriptor, trainDescriptor, wrongMatches);
  } else {
    return this->fastRobustMatch(queryDescriptor, trainDescriptor, wrongMatches);
  }
}

std::vector<cv::DMatch> RobustMatchingStrategy::robustMatch(const cv::Mat &queryDescriptor, const cv::Mat &trainDescriptor, std::vector<cv::DMatch> *wrongMatches)
{
  std::vector<cv::DMatch> goodMatches;

  std::vector<std::vector<cv::DMatch>> matches12;
  std::vector<std::vector<cv::DMatch>> matches21;

  bool err = mDescriptorMatcher->match(queryDescriptor, trainDescriptor, matches12);
  if (err) return goodMatches;

  err = mDescriptorMatcher->match(trainDescriptor, queryDescriptor, matches21);
  if (err) return goodMatches;

  std::vector<std::vector<cv::DMatch>> wrong_matches12;
  std::vector<std::vector<cv::DMatch>> wrong_matches21;
  std::vector<std::vector<cv::DMatch>> good_matches12 = this->ratioTest(matches12, this->ratio(), &wrong_matches12);
  std::vector<std::vector<cv::DMatch>> good_matches21 = this->ratioTest(matches21, this->ratio(), &wrong_matches21);

  matches12.clear();
  matches21.clear();

  if (wrongMatches){
    for (size_t i = 0; i < wrong_matches12.size(); i++){
      wrongMatches->push_back(wrong_matches12[i][0]);
    }
  }


  goodMatches = this->crossCheckTest(good_matches12, good_matches21, wrongMatches);

  return goodMatches;
}

std::vector<cv::DMatch> RobustMatchingStrategy::fastRobustMatch(const cv::Mat &queryDescriptor, const cv::Mat &trainDescriptor, std::vector<cv::DMatch> *wrongMatches)
{
  std::vector<cv::DMatch> goodMatches;

  std::vector<std::vector<cv::DMatch>> matches;
  bool err = mDescriptorMatcher->match(queryDescriptor, trainDescriptor, matches);
  if (err) return goodMatches;

  std::vector<std::vector<cv::DMatch>> ratio_test_wrong_matches;
  std::vector<std::vector<cv::DMatch>> ratio_test_matches = this->ratioTest(matches, this->ratio(), &ratio_test_wrong_matches);

  for (auto &match : ratio_test_matches){
    goodMatches.push_back(match[0]);
  }

  if (wrongMatches) {
    for (auto &wrong_match : ratio_test_wrong_matches){
      wrongMatches->push_back(wrong_match[0]);
    }
  }

  return goodMatches;
}

bool RobustMatchingStrategy::compute(const cv::Mat &queryDescriptor,
                                     const cv::Mat &trainDescriptor,
                                     const std::vector<cv::KeyPoint> &keypoints1,
                                     const std::vector<cv::KeyPoint> &keypoints2,
                                     std::vector<cv::DMatch> *goodMatches,
                                     std::vector<cv::DMatch> *wrongMatches,
                                     const QSize &queryImageSize,
                                     const QSize &trainImageSize)
{
  try {
    *goodMatches = this->match(queryDescriptor, trainDescriptor, wrongMatches);
    *goodMatches = this->geometricFilter(*goodMatches, keypoints1, keypoints2, wrongMatches);
  } catch(std::exception &e){
    return true;
  }
  return false;
}


/*----------------------------------------------------------------*/


GmsProperties::GmsProperties()
  : IGms(),
    mRotation(true),
    mScale(true),
    mThreshold(0.6)
{

}

void GmsProperties::reset()
{
  mRotation = true;
  mScale = true;
  mThreshold = 6.0;
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


GsmStrategy::GsmStrategy(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher)
  : GmsProperties(),
    MatchingAlgorithm(),
    mDescriptorMatcher(descriptorMatcher)
{
}

GsmStrategy::GsmStrategy(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher,
                         bool rotation,
                         bool scale,
                         double threshold)
  : GmsProperties(),
    MatchingAlgorithm(),
    mDescriptorMatcher(descriptorMatcher)
{
  this->setRotation(rotation);
  this->setScale(scale);
  this->setThreshold(threshold);
}

GsmStrategy::~GsmStrategy()
{

}

bool GsmStrategy::compute(const cv::Mat &queryDescriptor,
                          const cv::Mat &trainDescriptor,
                          const std::vector<cv::KeyPoint> &keypoints1,
                          const std::vector<cv::KeyPoint> &keypoints2,
                          std::vector<cv::DMatch> *goodMatches,
                          std::vector<cv::DMatch> *wrongMatches,
                          const QSize &queryImageSize,
                          const QSize &trainImageSize)
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR >= 4 && CV_VERSION_REVISION >= 1 )
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
  TL_COMPILER_WARNING("'matchGMS' not supported in OpenCV versions < 3.3.1")
#endif
  return false;
}


/*----------------------------------------------------------------*/



void matchesWrite(const QString &fname,
                  const std::vector<cv::DMatch> &matches,
                  const std::vector<cv::DMatch> &wrongMatches)
{

  QByteArray ba = fname.toLocal8Bit();
  const char *matches_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  int flags = 0;
  if (ext.compare("xml") == 0) {
    flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML;
  } else if (ext.compare("yml") == 0) {
    flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML;
  } else if (ext.compare("bin") == 0) {

  } else {
    ba = ext.toLocal8Bit();
    const char *cext = ba.data();
    msgError("file extension '%s' not valid", cext);
    return;
  }

  if (ext.compare("bin") == 0) {
    FILE* fp = std::fopen(matches_file, "wb");
    if (fp) {
      // Cabecera
      uint64_t size = matches.size();
      uint64_t size_wm = wrongMatches.size();
      std::fwrite("TIDOPLIB-Matching-#01", sizeof("TIDOPLIB-Matching-#01"), 1, fp);
      std::fwrite(&size, sizeof(uint64_t), 1, fp);
      std::fwrite(&size_wm, sizeof(uint64_t), 1, fp);
      char extraHead[100]; // Reserva de espacio para futuros usos
      std::fwrite(&extraHead, sizeof(char), 100, fp);
      //Cuerpo
      for (size_t i = 0; i < size; i++) {
        std::fwrite(&matches[i].queryIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&matches[i].trainIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&matches[i].imgIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&matches[i].distance, sizeof(float), 1, fp);
      }
      for (size_t i = 0; i < size_wm; i++) {
        std::fwrite(&wrongMatches[i].queryIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&wrongMatches[i].trainIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&wrongMatches[i].imgIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&wrongMatches[i].distance, sizeof(float), 1, fp);
      }
      std::fclose(fp);
    } else {
      //msgError("No pudo escribir archivo %s", matches_file);
    }
  } else {
    cv::FileStorage fs(matches_file, flags);
    if (fs.isOpened()) {
      if (!matches.empty()) write(fs, "matches", matches);
      if (!wrongMatches.empty()) write(fs, "wrong_matches", wrongMatches);
      fs.release();
    } else {
      //msgError("No pudo escribir archivo %s", matches_file);
    }
  }
}

void matchesRead(const QString &fname,
                 std::vector<cv::DMatch> *matches,
                 std::vector<cv::DMatch> *wrongMatches)
{
  QByteArray ba = fname.toLocal8Bit();
  const char *feat_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  if (ext.isEmpty() == false) {
    if (ext.compare("bin") == 0) {
      if (FILE* fp = std::fopen(feat_file, "rb")) {
        //cabecera
        char h[22];
        uint64_t size;
        uint64_t size_wm;
        char extraHead[100];
        std::fread(h, sizeof(char), 22, fp);
        std::fread(&size, sizeof(uint64_t), 1, fp);
        std::fread(&size_wm, sizeof(uint64_t), 1, fp);
        std::fread(&extraHead, sizeof(char), 100, fp);
        //Cuerpo
        if (matches){
          matches->resize(static_cast<size_t>(size));
          for (auto &match : *matches) {
            std::fread(&match.queryIdx, sizeof(int32_t), 1, fp);
            std::fread(&match.trainIdx, sizeof(int32_t), 1, fp);
            std::fread(&match.imgIdx, sizeof(int32_t), 1, fp);
            std::fread(&match.distance, sizeof(float), 1, fp);
          }
        } else {
          std::fseek(fp, sizeof(int32_t)*3*sizeof(float)*size, SEEK_CUR);
        }
        if (wrongMatches){
          wrongMatches->resize(static_cast<size_t>(size_wm));
          for (auto &match : *wrongMatches) {
            std::fread(&match.queryIdx, sizeof(int32_t), 1, fp);
            std::fread(&match.trainIdx, sizeof(int32_t), 1, fp);
            std::fread(&match.imgIdx, sizeof(int32_t), 1, fp);
            std::fread(&match.distance, sizeof(float), 1, fp);
          }
        }

        std::fclose(fp);
      } /*else
        msgError("No pudo leer archivo %s", fname);*/
    } else if (ext.compare("xml") == 0 || ext.compare("yml") == 0) {

      cv::FileStorage fs(feat_file, cv::FileStorage::READ);
      if (fs.isOpened()) {
        if (matches) {
          matches->resize(0);
          fs["matches"] >> *matches;
        }
        if (wrongMatches) {
          wrongMatches->resize(0);
          fs["wrong_matches"] >> *wrongMatches;
        }
        fs.release();
      } else {
        //msgError("No pudo leer archivo %s", fname.c_str());
      }
    }
  } /*else msgError("Fichero no valido: %s", fname);*/
}


void passPointsWrite(const QString &fname,
                     const std::vector<std::vector<std::pair<QString, int>>> &pass_points)
{
  std::ofstream ofs(fname.toStdString(), std::ofstream::trunc);
  if (ofs.is_open()){

    for (size_t i = 0; i < pass_points.size(); i++) {

      ofs << i;

      for (size_t j = 0; j < pass_points[i].size(); j++){
        ofs << " " << pass_points[i][j].first.toStdString()
            << " " << pass_points[i][j].second;
      }

      ofs << std::endl;
    }

    ofs.close();
  }
}

void passPointsRead(const QString &fname, std::vector<std::vector<std::pair<QString, int>>> &pass_points)
{
  pass_points.resize(0);
  std::ifstream ifs(fname.toStdString());
  std::string line;
  if (ifs.is_open()) {

    int r = 0;
    while (std::getline(ifs, line)) {
      QStringList list = QString(line.c_str()).split(" ");
      int size = list.size();
      if (size >= 1){
        if (size == 1 || size % 2 == 0){
          /// deleted point
          pass_points.push_back(std::vector<std::pair<QString, int>>());
        } else {
          std::vector<std::pair<QString, int>> pass_point;
          for(int i = 1; i < size; i++){
            QString idImage = list[i];
            int idx = list[++i].toInt();
            pass_point.push_back(std::make_pair(idImage, idx));
          }
          pass_points.push_back(pass_point);
        }
      }

      r++;
    }

    ifs.close();
  }
}


} // namespace photomatch
