#ifndef ORB_KPDETPROCESS_H
#define ORB_KPDETPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class ORB_KPDetProcess: public ProcessConcurrent
{
public:
    ORB_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,int maxFeatures,QString imageName);
    ~ORB_KPDetProcess();
    void run();

private:
    QString mImageName;
    cv::Mat &mCvImg;
    int mMaxFeatures;
    std::vector<cv::KeyPoint> &mCvKey;
};

#endif // ORB_KPDETPROCESS_H
