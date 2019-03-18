#ifndef WALLISFILTER_PROCESS_H
#define WALLISFILTER_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <QDir>
#include "opencv/cv.hpp"

class WallisFilter_Process:public ProcessConcurrent
{
public:
    WallisFilter_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right,float contrast,float brightness, int imposedAverage,int imposedLocalStandardDeviation,int kernelSize, QDir outputDir);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    QDir mOutputDir;

    float mContrast;
    float mBrightness;
    int mImposedAverage;
    int mImposedLocalStandardDeviation;
    int mKernelSize;
};

#endif // WALLISFILTER_PROCESS_H
