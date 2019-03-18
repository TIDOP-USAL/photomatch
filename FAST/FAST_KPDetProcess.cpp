#include "FAST_KPDetProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
FAST_KPDetProcess::FAST_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName):
    mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

FAST_KPDetProcess::~FAST_KPDetProcess()
{

}

void FAST_KPDetProcess::run(){
    emit newStdData("Searching FAST key-points for image "+mImageName);
    cv::Ptr<cv::FastFeatureDetector> detector =  cv::FastFeatureDetector::create();
    detector->detect(mCvImg,mCvKey);
    emit newStdData("FAST Key-points found in image "+mImageName+": "+QString::number(mCvKey.size()));

}
