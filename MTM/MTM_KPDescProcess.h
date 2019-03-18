#ifndef MTM_KPDESCPROCESS_H
#define MTM_KPDESCPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

using namespace cv;

class MTM_KPDescProcess: public ProcessConcurrent
{
public:
    MTM_KPDescProcess(cv::Mat &cvImgLeft,cv::Mat &cvImgRight, std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,std::vector<std::vector<cv::DMatch>> &matchesL2R,std::vector<std::vector<cv::DMatch>> &matchesR2L,int sizePatch,int nBins,QString leftImageName,QString rightImageName);
    ~MTM_KPDescProcess();
    void run();

private:
    QString mLeftImageName,mRightImageName;
    cv::Mat &mCvImgLeft,&mCvImgRight;
    std::vector<cv::KeyPoint> &mCvkeyLeft,&mCvkeyRight;
    std::vector<std::vector<cv::DMatch>> &mMatchesL2R,&mMatchesR2L;
    int mSizePatch, mNBins;
    void normalizepatch(int i, cv::Mat &output,int leftorright);
};

#endif // MTM_KPDescProcess_H
