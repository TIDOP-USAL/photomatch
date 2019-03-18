#ifndef BRIEF_KPDESCPROCESS_H
#define BRIEF_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class BRIEF_KPDescProcess: public ProcessConcurrent
{
public:
    BRIEF_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~BRIEF_KPDescProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // BRIEF_KPDESCPROCESS_H
