#ifndef FME_BRISK_KPDESCPROCESS_H
#define FME_BRISK_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT BRISK_KPDescProcess
  : public ProcessConcurrent
{

public:

  BRISK_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName);
  ~BRISK_KPDescProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvkey;
  cv::Mat &mCvDesc;

};

#endif // FME_BRISK_KPDESCPROCESS_H
