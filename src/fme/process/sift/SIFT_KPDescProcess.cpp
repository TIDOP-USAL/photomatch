#include "SIFT_KPDescProcess.h"

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

SIFT_KPDescProcess::SIFT_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc, const QString &imageName)
  : mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

SIFT_KPDescProcess::~SIFT_KPDescProcess()
{

}

void SIFT_KPDescProcess::run()
{
  emit newStdData("Starting SIFT key-point description for image " + mImageName);
  Ptr<xfeatures2d::SIFT> detector = xfeatures2d::SIFT::create();
  //    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
  detector->compute(mCvImg, mCvkey, mCvDesc);
  emit newStdData("SIFT key-point description finished for image " + mImageName);
}

