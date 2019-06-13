#include "GFTT_KPDetProcess.h"

#include <opencv2/features2d.hpp>

using namespace cv;

GFTT_KPDetProcess::GFTT_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName)
  : mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

GFTT_KPDetProcess::~GFTT_KPDetProcess()
{

}
void GFTT_KPDetProcess::run()
{
  emit newStdData("Starting GFTT key-point description for image " + mImageName);
  Ptr<cv::GFTTDetector> detector = cv::GFTTDetector::create();
  detector->detect(mCvImg, mCvKey);
  emit newStdData("GFTT key-point description finished for image " + mImageName);
}

