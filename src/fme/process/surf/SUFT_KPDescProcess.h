#ifndef SUFT_KPDESCPROCESS_H
#define SUFT_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT SUFT_KPDescProcess
  : public ProcessConcurrent
{

public:

  SUFT_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName);
  ~SUFT_KPDescProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvkey;
  cv::Mat &mCvDesc;
};

#endif // SUFT_KPDESCPROCESS_H
