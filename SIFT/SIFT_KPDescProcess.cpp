#include "SIFT_KPDescProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
using namespace cv;

SIFT_KPDescProcess::SIFT_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName):
    mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

SIFT_KPDescProcess::~SIFT_KPDescProcess()
{

}

void SIFT_KPDescProcess::run(){
    emit newStdData("Starting SIFT key-point description for image "+mImageName);
    Ptr<xfeatures2d::SIFT> detector = xfeatures2d::SIFT::create();
//    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
    detector->compute(mCvImg,mCvkey,mCvDesc);
    emit newStdData("SIFT key-point description finished for image "+mImageName);
}

