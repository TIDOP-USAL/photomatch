#ifndef MSRCP2014_PROCESS_H
#define MSRCP2014_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class MSRCP2014_Process : public ProcessConcurrent
{
public:
    MSRCP2014_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right, QDir outputDir);
    virtual void run() override;

private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    QDir mOutputDir;
};

#endif // MSRCP2014_PROCESS_H
