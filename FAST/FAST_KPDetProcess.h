#ifndef FAST_KPDETPROCESS_H
#define FAST_KPDETPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class FAST_KPDetProcess: public ProcessConcurrent
{
public:
    FAST_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName);
    ~FAST_KPDetProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvKey;
};

#endif // FAST_KPDETPROCESS_H
