#ifndef FME_LATCH_KPDESCPROCESS_H
#define FME_LATCH_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT LATCH_KPDescProcess
  : public ProcessConcurrent
{

public:

    LATCH_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName);
    ~LATCH_KPDescProcess() override;

    void run() override;

private:

    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // FME_LATCH_KPDESCPROCESS_H
