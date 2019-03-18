#ifndef GFTT_KPDETPROCESS_H
#define GFTT_KPDETPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class GFTT_KPDetProcess: public ProcessConcurrent
{
public:
    GFTT_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName);
    ~GFTT_KPDetProcess();
    virtual void run();
private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvKey;
};

#endif // GFTT_KPDETPROCESS_H
