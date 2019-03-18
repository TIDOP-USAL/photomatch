#ifndef WANG_ZHENG_HU_LI2013_PROCESS_H
#define WANG_ZHENG_HU_LI2013_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class Wang_Zheng_Hu_Li2013_Process:public ProcessConcurrent
{
public:
    Wang_Zheng_Hu_Li2013_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right, QDir outputDir);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    QDir mOutputDir;
};

#endif // WANG_ZHENG_HU_LI2013_PROCESS_H
