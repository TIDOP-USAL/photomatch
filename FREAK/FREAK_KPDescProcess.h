#ifndef FREAK_KPDESCPROCESS_H
#define FREAK_KPDESCPROCESS_H


#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"
class FREAK_KPDescProcess: public ProcessConcurrent
{
public:
    FREAK_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~FREAK_KPDescProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // FREAK_KPDESCPROCESS_H
