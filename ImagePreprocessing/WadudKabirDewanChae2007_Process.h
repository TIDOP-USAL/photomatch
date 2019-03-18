#ifndef WADUDKABIRDEWANCHAE2007_PROCESS_H
#define WADUDKABIRDEWANCHAE2007_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class WadudKabirDewanChae2007_Process:public ProcessConcurrent
{
public:
    WadudKabirDewanChae2007_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right,int power, QDir outputDir);
    virtual void run();
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    int mPower;
    QDir mOutputDir;
};

#endif // WADUDKABIRDEWANCHAE2007_PROCESS_H
