#ifndef SURF_KPDETPROCESS_H
#define SURF_KPDETPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class SURF_KPDetProcess: public ProcessConcurrent
{
public:
    SURF_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,QString imageName);
    ~SURF_KPDetProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvKey;
};

#endif // SURF_KPDETPROCESS_H
