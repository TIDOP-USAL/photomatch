#include "FLANNMatcherProcess.h"

#include <opencv2/features2d.hpp>

using namespace cv;

FLANNMatcherProcess::FLANNMatcherProcess(cv::Mat &cvImgLeft, cv::Mat &cvImgRight,
                                         std::vector<cv::KeyPoint> &cvkeyLeft,
                                         std::vector<cv::KeyPoint> &cvkeyRight,
                                         cv::Mat &cvDescLeft, cv::Mat &cvDescRight,
                                         std::vector<cv::DMatch> &correctMatches,
                                         std::vector<cv::DMatch> &wrongMatches, 
                                         bool haveGroundTruth, cv::Mat &groundTruth, 
                                         const QString &leftImageName, const QString &rightImageName)
  : mCvImgLeft(cvImgLeft),
    mCvImgRight(cvImgRight),
    mCvKeyLeft(cvkeyLeft),
    mCvKeyRight(cvkeyRight),
    mCvDescLeft(cvDescLeft),
    mCvDescRight(cvDescRight),
    mLeftImageName(leftImageName),
    mRightImageName(rightImageName),
    mCorrectMatches(correctMatches),
    mWrongMatches(wrongMatches),
    mHaveGroundTruth(haveGroundTruth),
    mGroundTruth(groundTruth)
{

}

FLANNMatcherProcess::~FLANNMatcherProcess()
{

}

void FLANNMatcherProcess::run() 
{
  emit newStdData("Starting FLANN matching");

  //const cv::Ptr<cv::flann::IndexParams> &indexParams = new cv::flann::KDTreeIndexParams(1);
  //const cv::Ptr<cv::flann::SearchParams> &searchParams = new cv::flann::SearchParams(64);

  // Match using Flann
  cv::Mat indexMat;
  cv::FlannBasedMatcher matcher(makePtr<flann::KDTreeIndexParams>(1), makePtr<flann::SearchParams>(64));
  std::vector< cv::DMatch > matches;
  matcher.match(mCvDescLeft, mCvDescRight, matches);
  double max_dist = 0; double min_dist = 100;

  //-- Quick calculation of max and min distances between keypoints
  for (int i = 0; i < mCvDescLeft.rows; i++)
  {
    double dist = matches[i].distance;
    if (dist < min_dist) min_dist = dist;
    if (dist > max_dist) max_dist = dist;
  }

  printf("-- Max dist : %f \n", max_dist);
  printf("-- Min dist : %f \n", min_dist);

  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
  //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
  //-- small)
  //-- PS.- radiusMatch can also be used here.

  std::vector<cv::DMatch> tempMatches;

  for (int i = 0; i < mCvDescLeft.rows; i++) {
    if (matches[i].distance <= max(2 * min_dist, 0.02)) {
      tempMatches.push_back(matches[i]);
    }
  }

  cv::Mat rot_mat;

  if (mHaveGroundTruth) {
    mGroundTruth.copyTo(rot_mat);

  } else {
    rot_mat = cv::Mat::eye(3, 3, CV_32F);
  }

  if (mHaveGroundTruth) {
    emit newStdData("Starting ground truth evaluation");

    for (size_t j = 0; j < tempMatches.size(); ++j) {
      float repeteability = 0;
      int corres = 0;
      cv::DMatch auxxxx;
      auxxxx = tempMatches[j];
      std::vector<cv::KeyPoint> key1;
      std::vector<cv::KeyPoint> key2;
      key1.push_back(mCvKeyLeft[auxxxx.queryIdx]);
      key2.push_back(mCvKeyRight[auxxxx.trainIdx]);
      //          std::vector<cv::DMatch> prueba;
      cv::evaluateFeatureDetector(mCvImgLeft, mCvImgRight, rot_mat, &key1, &key2, repeteability, corres);
      if (corres > 0) mCorrectMatches.push_back(tempMatches[j]);
      else mWrongMatches.push_back(tempMatches[j]);

    }
    emit newStdData("Correct matches: " + QString::number(mCorrectMatches.size()));
    emit newStdData("Wrong matches: " + QString::number(mWrongMatches.size()));
  } else {
    mCorrectMatches = tempMatches;
    emit newStdData("Correct matches: " + QString::number(mCorrectMatches.size()));
  }

  emit newStdData("Matching process finished.");

}
