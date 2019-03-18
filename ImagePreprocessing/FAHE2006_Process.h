#ifndef FAHE2006_PROCESS_H
#define FAHE2006_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class FAHE2006_Process:public ProcessConcurrent
{
public:
    FAHE2006_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right,cv::Size blockSize, QDir outputDir);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    cv::Size mBlockSize;
    QDir mOutputDir;
};

#endif // FAHE2006_PROCESS_H
