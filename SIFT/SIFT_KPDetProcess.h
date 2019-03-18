#ifndef SIFT_KPDETPROCESS_H
#define SIFT_KPDETPROCESS_H

#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"


class SIFT_KPDetProcess: public ProcessConcurrent
{
public:
    SIFT_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName);
    ~SIFT_KPDetProcess();
    virtual void run();
private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvKey;
};

#endif // SIFT_KPDETPROCESS_H
