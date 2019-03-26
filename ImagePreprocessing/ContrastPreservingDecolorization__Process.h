#ifndef CONTRASTPRESERVINGDECOLORIZATION_PROCESS_H
#define CONTRASTPRESERVINGDECOLORIZATION_PROCESS_H

#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class ContrastPreservingDecolorization__Process : public ProcessConcurrent
{
public:
    ContrastPreservingDecolorization__Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, QDir outputDir);
    virtual void run() override;

private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    QDir mOutputDir;
};

#endif // CONTRASTPRESERVINGDECOLORIZATION_PROCESS_H
