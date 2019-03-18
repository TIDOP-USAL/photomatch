#include "SIFT_KPDetProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
using namespace cv;

SIFT_KPDetProcess::SIFT_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName):
    mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

SIFT_KPDetProcess::~SIFT_KPDetProcess()
{

}

void SIFT_KPDetProcess::run(){
    emit newStdData("Searching SIFT key-points for image "+mImageName);
    Ptr<xfeatures2d::SIFT> detector = xfeatures2d::SIFT::create();
//    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
    detector->detect(mCvImg,mCvKey);
    emit newStdData("SIFT Key-points found in image "+mImageName+": "+QString::number(mCvKey.size()));
}
