#include "SUFT_KPDescProcess.h"

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

SUFT_KPDescProcess::SUFT_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName) 
  : mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

SUFT_KPDescProcess::~SUFT_KPDescProcess()
{

}

void SUFT_KPDescProcess::run()
{
  emit newStdData("Starting SURF key-point description for image " + mImageName);
  Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
  //    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
  detector->compute(mCvImg, mCvkey, mCvDesc);
  emit newStdData("SURF key-point description finished for image " + mImageName);
}
