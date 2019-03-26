#ifndef POHE2013_PROCESS_H
#define POHE2013_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class POHE2013_Process : public ProcessConcurrent
{
public:
    POHE2013_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right, QDir outputDir);
    virtual void run() override;

private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    QDir mOutputDir;
};

#endif // POHE2013_PROCESS_H
