#ifndef DAISY_KPDESCPROCESS_H
#define DAISY_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class DAISY_KPDescProcess: public ProcessConcurrent
{
public:
    DAISY_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~DAISY_KPDescProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // DAISY_KPDESCPROCESS_H
