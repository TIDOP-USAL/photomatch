#include "SURF_KPDetProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
SURF_KPDetProcess::SURF_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName):
        mCvImg(cvImg),
        mCvKey(cvKey),
        mImageName(imageName)
{

}

SURF_KPDetProcess::~SURF_KPDetProcess()
{

}

void SURF_KPDetProcess::run(){
    emit newStdData("Searching SURF key-points for image "+mImageName);
//    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
    cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
    detector->detect(mCvImg,mCvKey);
    emit newStdData("SURF Key-points found in image "+mImageName+": "+QString::number(mCvKey.size()));
}

