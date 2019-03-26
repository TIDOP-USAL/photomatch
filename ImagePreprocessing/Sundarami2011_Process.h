#ifndef SUNDARAMI2011_PROCESS_H
#define SUNDARAMI2011_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>


class Sundarami2011_Process : public ProcessConcurrent
{
public:
    Sundarami2011_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, cv::Size blockSize, float L, float phi, QDir outputDir);
    virtual void run() override;

private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    cv::Size mBlockSize;
    float mL;
    float mPhi;
    QDir mOutputDir;
};

#endif // SUNDARAMI2011_PROCESS_H
