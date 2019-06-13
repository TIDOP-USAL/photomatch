#ifndef FME_FREAK_KPDESCPROCESS_H
#define FME_FREAK_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT FREAK_KPDescProcess
  : public ProcessConcurrent
{

public:

  FREAK_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName);
  ~FREAK_KPDescProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvkey;
  cv::Mat &mCvDesc;

};

#endif // FME_FREAK_KPDESCPROCESS_H
