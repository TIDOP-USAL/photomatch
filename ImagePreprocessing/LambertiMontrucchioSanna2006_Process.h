#ifndef LAMBERTIMONTRUCCHIOSANNA2006_PROCESS_H
#define LAMBERTIMONTRUCCHIOSANNA2006_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class LambertiMontrucchioSanna2006_Process:public ProcessConcurrent
{
public:
    LambertiMontrucchioSanna2006_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right,cv::Size blockSize,cv::Size blockRegions, QDir outputDir);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    cv::Size mBlockSize;
    cv::Size mBlockRegions;
    QDir mOutputDir;
};

#endif // LAMBERTIMONTRUCCHIOSANNA2006_PROCESS_H
