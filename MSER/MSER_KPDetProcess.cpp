#include "MSER_KPDetProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
using namespace cv;
MSER_KPDetProcess::MSER_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName):
    mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

MSER_KPDetProcess::~MSER_KPDetProcess()
{

}

void MSER_KPDetProcess::run(){
    emit newStdData("Searching MSER key-points for image "+mImageName);
    cv::Ptr<cv::MSER> detector =  cv::MSER::create();
    detector->detect(mCvImg,mCvKey);
    emit newStdData("MSER Key-points found in image "+mImageName+": "+QString::number(mCvKey.size()));
}
