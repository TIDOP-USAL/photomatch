#include "LUCID_KPDescProcess.h"

#include <opencv2/xfeatures2d.hpp>

using namespace cv;

LUCID_KPDescProcess::LUCID_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc, const QString &imageName)
  : mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

LUCID_KPDescProcess::~LUCID_KPDescProcess()
{

}
void LUCID_KPDescProcess::run()
{
  emit newStdData("Starting LUCID key-point description for image " + mImageName);
  Ptr<xfeatures2d::LUCID> detector = xfeatures2d::LUCID::create(2, 2);
  detector->compute(mCvImg, mCvkey, mCvDesc);
  emit newStdData("LUCID key-point description finished for image " + mImageName);
}
