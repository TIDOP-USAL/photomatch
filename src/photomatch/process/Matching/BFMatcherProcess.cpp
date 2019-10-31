#include "BFMatcherProcess.h"

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

BFMatcherProcess::BFMatcherProcess(cv::Mat &cvDescLeft, cv::Mat &cvDescRight, 
                                   std::vector<std::vector<cv::DMatch>> &matchesL2R,
                                   std::vector<std::vector<cv::DMatch>> &matchesR2L, 
                                   const QString &leftImageName, const QString &rightImageName)
  : mCvDescLeft(cvDescLeft),
    mCvDescRight(cvDescRight),
    mCvMatchesL2R(matchesL2R),
    mCvMatchesR2L(matchesR2L),
    mLeftImageName(leftImageName),
    mRightImageName(rightImageName)
{

}

BFMatcherProcess::~BFMatcherProcess()
{

}

void BFMatcherProcess::run() 
{
  emit newStdData("Starting brute force matching");

  BFMatcher matcher(NORM_L2);
  // from image 1 to image 2
  // based on k nearest neighbours (with k=2)
  matcher.knnMatch(mCvDescLeft, mCvDescRight,
    mCvMatchesL2R, // vector of matches (up to 2 per entry)
    2); // return 2 nearest neighbours
    // from image 2 to image 1
    // based on k nearest neighbours (with k=2)
  matcher.knnMatch(mCvDescRight, mCvDescLeft,
    mCvMatchesR2L, // vector of matches (up to 2 per entry)
    2); // return 2 nearest neighbours
  emit newStdData("Matching process finished.");
  emit newStdData("Matches found from image " + mLeftImageName + " to image " + mRightImageName + ": " + QString::number(mCvMatchesL2R.size() * 2));
  emit newStdData("Matches found from image " + mRightImageName + " to image " + mLeftImageName + ": " + QString::number(mCvMatchesR2L.size() * 2));
}
