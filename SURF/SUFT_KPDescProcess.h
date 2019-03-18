#ifndef SUFT_KPDESCPROCESS_H
#define SUFT_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class SUFT_KPDescProcess: public ProcessConcurrent
{
public:
    SUFT_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~SUFT_KPDescProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // SUFT_KPDESCPROCESS_H
