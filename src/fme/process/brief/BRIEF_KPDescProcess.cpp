#include "BRIEF_KPDescProcess.h"

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

BRIEF_KPDescProcess::BRIEF_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName)
  : mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

BRIEF_KPDescProcess::~BRIEF_KPDescProcess()
{

}

void BRIEF_KPDescProcess::run() 
{
  emit newStdData("Starting BRIEF key-point description for image " + mImageName);
  Ptr<xfeatures2d::BriefDescriptorExtractor> detector = xfeatures2d::BriefDescriptorExtractor::create();
  //    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
  detector->compute(mCvImg, mCvkey, mCvDesc);
  emit newStdData("BRIEF key-point description finished for image " + mImageName);
}
