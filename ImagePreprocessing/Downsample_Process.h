#ifndef DOWNSAMPLE_PROCESS_H
#define DOWNSAMPLE_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
class Downsample_Process:public ProcessConcurrent
{
public:
    Downsample_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right, int resolution);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    int mResolution;
};

#endif // DOWNSAMPLE_PROCESS_H
