#ifndef RAJUNAIR2014_PROCESS_H
#define RAJUNAIR2014_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class RajuNair2014_Process:public ProcessConcurrent
{
public:
    RajuNair2014_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right, QDir outputDir);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    QDir mOutputDir;
};

#endif // RAJUNAIR2014_PROCESS_H
