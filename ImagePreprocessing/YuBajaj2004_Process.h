#ifndef YUBAJAJ2004_PROCESS_H
#define YUBAJAJ2004_PROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class YuBajaj2004_Process : public ProcessConcurrent
{
public:
    YuBajaj2004_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, cv::Size blockSize, float c, bool anisotropicMode, float r, QDir outputDir);
    virtual void run() override;

private:
    cv::Mat& mCvImg_left;
    cv::Mat& mCvImg_right;
    cv::Size mBlockSize;
    float mC;
    bool mAnisotropicMode;
    float mR;
    QDir mOutputDir;
};

#endif // YUBAJAJ2004_PROCESS_H
