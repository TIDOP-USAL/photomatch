#include "FAST_KPDetProcess.h"

#include <opencv2/features2d.hpp>

FAST_KPDetProcess::FAST_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey, const QString &imageName)
  : mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

FAST_KPDetProcess::~FAST_KPDetProcess()
{

}

void FAST_KPDetProcess::run()
{
  emit newStdData("Searching FAST key-points for image " + mImageName);
  cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create();
  detector->detect(mCvImg, mCvKey);
  emit newStdData("FAST Key-points found in image " + mImageName + ": " + QString::number(mCvKey.size()));
}
