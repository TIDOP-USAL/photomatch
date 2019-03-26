#ifndef CELIKTJAHJADI2012_PROCESS_H
#define CELIKTJAHJADI2012_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class CelikTjahjadi2012_Process : public ProcessConcurrent
{
public:
    CelikTjahjadi2012_Process(cv::Mat &cvImg_Left,cv::Mat &cvImg_Right,int n, QDir outputDir);
    virtual void run() override;
private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    int mN;
    QDir mOutputDir;
};

#endif // CELIKTJAHJADI2012_PROCESS_H
