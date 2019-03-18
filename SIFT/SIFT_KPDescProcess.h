#ifndef SIFT_KPDESCPROCESS_H
#define SIFT_KPDESCPROCESS_H

#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"
class SIFT_KPDescProcess: public ProcessConcurrent
{
public:
    SIFT_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~SIFT_KPDescProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // SIFT_KPDESCPROCESS_H
