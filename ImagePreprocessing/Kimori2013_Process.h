#ifndef KIMORI2013_PROCESS_H
#define KIMORI2013_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class Kimori2013_Process : public ProcessConcurrent
{
public:
    Kimori2013_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right,cv::Size blockSize, QDir outputDir);
    virtual void run() override;

private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    cv::Size mBlockSize;
    QDir mOutputDir;
};

#endif // KIMORI2013_PROCESS_H
