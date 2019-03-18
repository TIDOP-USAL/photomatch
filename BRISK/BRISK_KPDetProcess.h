#ifndef BRISK_KPDETPROCESS_H
#define BRISK_KPDETPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class BRISK_KPDetProcess: public ProcessConcurrent
{
public:
    BRISK_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName);
    ~BRISK_KPDetProcess();
    virtual void run();
private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvKey;
};

#endif // BRISK_KPDETPROCESS_H
