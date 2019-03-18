#include "FREAK_KPDescProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
using namespace cv;
FREAK_KPDescProcess::FREAK_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName):
    mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc),
    mImageName(imageName)
{

}

FREAK_KPDescProcess::~FREAK_KPDescProcess()
{

}
void FREAK_KPDescProcess::run(){
    emit newStdData("Starting FREAK key-point description for image "+mImageName);
    Ptr<xfeatures2d::FREAK> detector = xfeatures2d::FREAK::create();
//    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);
    detector->compute(mCvImg,mCvkey,mCvDesc);
    emit newStdData("FREAK key-point description finished for image "+mImageName);
}
