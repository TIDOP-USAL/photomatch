#ifndef FLANNMATCHERPROCESS_H
#define FLANNMATCHERPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class FLANNMatcherProcess: public ProcessConcurrent
{
public:
    FLANNMatcherProcess(cv::Mat &cvImgLeft,cv::Mat &cvImgRight,std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,cv::Mat &cvDescLeft,cv::Mat &cvDescRight,std::vector<cv::DMatch> &correctMatches,std::vector<cv::DMatch> &wrongMatches,bool haveGroundTruth,cv::Mat &groundTruth,QString leftImageName,QString rightImageName);
    ~FLANNMatcherProcess();
    void run();

private:
    QString mLeftImageName,mRightImageName;
    cv::Mat &mCvImgLeft,&mCvImgRight;
    std::vector<cv::KeyPoint> &mCvKeyLeft, &mCvKeyRight;
    cv::Mat &mCvDescLeft,&mCvDescRight;
    std::vector<cv::DMatch> &mCorrectMatches,&mWrongMatches;
    bool mHaveGroundTruth;
    cv::Mat &mGroundTruth;
};

#endif // FLANNMATCHERPROCESS_H
