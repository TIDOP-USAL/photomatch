#include "GFTT_KPDetProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
using namespace cv;
GFTT_KPDetProcess::GFTT_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName):
    mCvImg(cvImg),
    mCvKey(cvKey),
    mImageName(imageName)
{

}

GFTT_KPDetProcess::~GFTT_KPDetProcess()
{

}
void GFTT_KPDetProcess::run(){
    emit newStdData("Starting GFTT key-point description for image "+mImageName);
    Ptr<cv::GFTTDetector> detector = cv::GFTTDetector::create();
    detector->detect(mCvImg,mCvKey);
    emit newStdData("GFTT key-point description finished for image "+mImageName);

}

