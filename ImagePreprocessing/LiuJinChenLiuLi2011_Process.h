#ifndef LIUJINCHENLIULI2011_PROCESS_H
#define LIUJINCHENLIULI2011_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>


class LiuJinChenLiuLi2011_Process:public ProcessConcurrent
{
public:
    LiuJinChenLiuLi2011_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right,cv::Size blockSize, QDir outputDir);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    cv::Size mBlockSize;
    QDir mOutputDir;
};

#endif // LIUJINCHENLIULI2011_PROCESS_H
