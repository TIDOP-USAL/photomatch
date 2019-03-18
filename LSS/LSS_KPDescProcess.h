#ifndef LSS_KPDETPROCESS_H
#define LSS_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class LSS_KPDescProcess: public ProcessConcurrent
{
public:
    LSS_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,cv::Mat &cvDesc,QString imageName);
    ~LSS_KPDescProcess();
    void run();
private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // LSS_KPDescProcess_H
