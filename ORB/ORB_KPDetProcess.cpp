#include "ORB_KPDetProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
ORB_KPDetProcess::ORB_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,int maxFeatures,QString imageName):
    mCvImg(cvImg),
    mCvKey(cvKey),
    mMaxFeatures(maxFeatures),
    mImageName(imageName)
{

}

ORB_KPDetProcess::~ORB_KPDetProcess()
{

}

void ORB_KPDetProcess::run(){
    emit newStdData("Searching ORB key-points for image "+mImageName);
    cv::Ptr<cv::ORB> detector =  cv::ORB::create();
    detector->setMaxFeatures(mMaxFeatures);
    detector->detect(mCvImg,mCvKey);
    emit newStdData("ORB Key-points found in image "+mImageName+": "+QString::number(mCvKey.size()));

}

