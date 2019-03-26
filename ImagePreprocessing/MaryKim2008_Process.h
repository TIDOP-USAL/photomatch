#ifndef MARYKIM2008_PROCESS_H
#define MARYKIM2008_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class MaryKim2008_Process : public ProcessConcurrent
{
public:
    MaryKim2008_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, int morD, int r, QDir outputDir);
    virtual void run() override;

private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    int mMorD;
    int mR;
    QDir mOutputDir;
};

#endif // MARYKIM2008_PROCESS_H
