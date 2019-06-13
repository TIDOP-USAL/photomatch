#include "MSER_KPDetProcess.h"

#include <opencv2/features2d.hpp>

using namespace cv;

MSER_KPDetProcess::MSER_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey, const QString &imageName)
  : mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

MSER_KPDetProcess::~MSER_KPDetProcess()
{

}

void MSER_KPDetProcess::run()
{
  emit newStdData("Searching MSER key-points for image " + mImageName);
  cv::Ptr<cv::MSER> detector = cv::MSER::create();
  detector->detect(mCvImg, mCvKey);
  emit newStdData("MSER Key-points found in image " + mImageName + ": " + QString::number(mCvKey.size()));
}
