#include "ORB_KPDetProcess.h"

#include <opencv2/features2d.hpp>

ORB_KPDetProcess::ORB_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, int maxFeatures, const QString &imageName)
  : mCvImg(cvImg),
    mCvKey(cvKey),
    mMaxFeatures(maxFeatures),
    mImageName(imageName)
{

}

ORB_KPDetProcess::~ORB_KPDetProcess()
{

}

void ORB_KPDetProcess::run()
{
  emit newStdData("Searching ORB key-points for image " + mImageName);
  cv::Ptr<cv::ORB> detector = cv::ORB::create();
  detector->setMaxFeatures(mMaxFeatures);
  detector->detect(mCvImg, mCvKey);
  emit newStdData("ORB Key-points found in image " + mImageName + ": " + QString::number(mCvKey.size()));
}

