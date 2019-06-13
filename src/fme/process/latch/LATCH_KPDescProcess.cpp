#include "LATCH_KPDescProcess.h"

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

LATCH_KPDescProcess::LATCH_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,
                                         cv::Mat &cvDesc, const QString &imageName)
  : mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

LATCH_KPDescProcess::~LATCH_KPDescProcess()
{

}

void LATCH_KPDescProcess::run() 
{
  emit newStdData("Starting FREAK key-point description for image " + mImageName);
  Ptr<xfeatures2d::LATCH> detector = xfeatures2d::LATCH::create();
  //    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
  detector->compute(mCvImg, mCvkey, mCvDesc);
  emit newStdData("FREAK key-point description finished for image " + mImageName);
}

