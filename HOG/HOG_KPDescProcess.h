#ifndef HOG_KPDESCPROCESS_H
#define HOG_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class HOG_KPDescProcess: public ProcessConcurrent
{
public:
    HOG_KPDescProcess(cv::Mat &cvImgLeft,cv::Mat &cvImgRight, std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,cv::Mat &cvDescLeft,cv::Mat &cvDescRight,int sizePatch,QString leftImageName,QString rightImageName);
    ~HOG_KPDescProcess();
    void run();

private:
    QString mLeftImageName,mRightImageName;
    cv::Mat &mCvImgLeft,&mCvImgRight;
    std::vector<cv::KeyPoint> &mCvkeyLeft,&mCvkeyRight;
    cv::Mat &mCvDescLeft,&mCvDescRight;
    int mSizePatch;
    void normalizepatch(int i, cv::Mat &output,int leftorright);
};

#endif // HOG_KPDESCPROCESS_H
