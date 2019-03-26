#ifndef LCE_BSESCS2014_PROCESS_H
#define LCE_BSESCS2014_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class LCE_BSESCS2014_Process : public ProcessConcurrent
{
public:
    LCE_BSESCS2014_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right,cv::Size blockSize, QDir outputDir);
    virtual void run() override;
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    cv::Size mBlockSize;
    QDir mOutputDir;
};

#endif // LCE_BSESCS2014_PROCESS_H
