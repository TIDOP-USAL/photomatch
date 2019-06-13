#ifndef FME_DOWNSAMPLE_PROCESS_H
#define FME_DOWNSAMPLE_PROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT Downsample_Process
  : public ProcessConcurrent
{

public:

    Downsample_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right, int resolution);
    ~Downsample_Process() override;
    
    void run() override;

private:

    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    int mResolution;
};

#endif // FME_DOWNSAMPLE_PROCESS_H
