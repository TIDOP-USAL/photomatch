#include "BRISK_KPDetProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
using namespace cv;
BRISK_KPDetProcess::BRISK_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName):
    mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

BRISK_KPDetProcess::~BRISK_KPDetProcess()
{

}

void BRISK_KPDetProcess::run(){
    emit newStdData("Starting BRISK key-point description for image "+mImageName);
    Ptr<cv::BRISK> detector = cv::BRISK::create();
    detector->detect(mCvImg,mCvKey);
    emit newStdData("BRISK key-point description finished for image "+mImageName);

}
