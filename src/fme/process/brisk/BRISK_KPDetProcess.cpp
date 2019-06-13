#include "BRISK_KPDetProcess.h"

#include <opencv2/features2d.hpp>

using namespace cv;

BRISK_KPDetProcess::BRISK_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName)
  : mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

BRISK_KPDetProcess::~BRISK_KPDetProcess()
{

}

void BRISK_KPDetProcess::run() 
{
  emit newStdData("Starting BRISK key-point description for image " + mImageName);
  Ptr<cv::BRISK> detector = cv::BRISK::create();
  detector->detect(mCvImg, mCvKey);
  emit newStdData("BRISK key-point description finished for image " + mImageName);
}
