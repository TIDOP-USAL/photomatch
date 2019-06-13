#include "ORB_KPDescProcess.h"

#include <opencv2/features2d.hpp>

using namespace cv;

ORB_KPDescProcess::ORB_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc, const QString &imageName)
  : mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

ORB_KPDescProcess::~ORB_KPDescProcess()
{

}

void ORB_KPDescProcess::run()
{
  emit newStdData("Starting ORB key-point description for image " + mImageName);
  Ptr<cv::ORB> detector = cv::ORB::create();
  detector->compute(mCvImg, mCvkey, mCvDesc);
  emit newStdData("ORB key-point description finished for image " + mImageName);
}
