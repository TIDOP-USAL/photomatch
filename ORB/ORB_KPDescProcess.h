#ifndef ORB_KPDESCPROCESS_H
#define ORB_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class ORB_KPDescProcess: public ProcessConcurrent
{
public:
    ORB_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~ORB_KPDescProcess();
    void run();
private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // ORB_KPDESCPROCESS_H
