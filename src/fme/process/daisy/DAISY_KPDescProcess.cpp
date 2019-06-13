#include "DAISY_KPDescProcess.h"

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

DAISY_KPDescProcess::DAISY_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName)
  : mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

DAISY_KPDescProcess::~DAISY_KPDescProcess()
{

}

void DAISY_KPDescProcess::run() 
{
  emit newStdData("Starting DAISY key-point description for image " + mImageName);
  Ptr<xfeatures2d::DAISY> detector = xfeatures2d::DAISY::create();
  //    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
  detector->compute(mCvImg, mCvkey, mCvDesc);
  emit newStdData("DAISY key-point description finished for image " + mImageName);
}
