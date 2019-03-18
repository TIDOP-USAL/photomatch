#ifndef MSER_KPDETPROCESS_H
#define MSER_KPDETPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class MSER_KPDetProcess: public ProcessConcurrent
{
public:
    MSER_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName);
    ~MSER_KPDetProcess();
    virtual void run();
private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvKey;
};

#endif // MSER_KPDETPROCESS_H
