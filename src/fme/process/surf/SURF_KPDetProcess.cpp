#include "SURF_KPDetProcess.h"

#include <opencv2/xfeatures2d.hpp>

SURF_KPDetProcess::SURF_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName) 
  : mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

SURF_KPDetProcess::~SURF_KPDetProcess()
{

}

void SURF_KPDetProcess::run()
{
  emit newStdData("Searching SURF key-points for image " + mImageName);
  //    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
  cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
  detector->detect(mCvImg, mCvKey);
  emit newStdData("SURF Key-points found in image " + mImageName + ": " + QString::number(mCvKey.size()));
}

