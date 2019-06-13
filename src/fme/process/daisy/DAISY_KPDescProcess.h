#ifndef DAISY_KPDESCPROCESS_H
#define DAISY_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT DAISY_KPDescProcess
  : public ProcessConcurrent
{

public:

    DAISY_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName);
    ~DAISY_KPDescProcess() override;

    void run() override;

private:

    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvkey;
    cv::Mat &mCvDesc;
};

#endif // DAISY_KPDESCPROCESS_H
