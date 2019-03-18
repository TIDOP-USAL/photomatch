#ifndef BFMATCHERPROCESS_H
#define BFMATCHERPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class BFMatcherProcess: public ProcessConcurrent
{
public:
    BFMatcherProcess(cv::Mat &cvDescLeft,cv::Mat &cvDescRight,std::vector<std::vector<cv::DMatch>> &matchesL2R,std::vector<std::vector<cv::DMatch>> &matchesR2L,QString leftImageName,QString rightImageName);
    ~BFMatcherProcess();
    void run();

private:
    QString mLeftImageName,mRightImageName;
    cv::Mat &mCvDescLeft,&mCvDescRight;
    std::vector<std::vector<cv::DMatch>> &mCvMatchesL2R, &mCvMatchesR2L;
};

#endif // BFMATCHERPROCESS_H
