#ifndef BRISK_KPDESCPROCESS_H
#define BRISK_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class BRISK_KPDescProcess: public ProcessConcurrent
{
public:
    BRISK_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~BRISK_KPDescProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // BRISK_KPDESCPROCESS_H
