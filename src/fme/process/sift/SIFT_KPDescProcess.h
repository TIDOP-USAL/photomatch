#ifndef SIFT_KPDESCPROCESS_H
#define SIFT_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT SIFT_KPDescProcess
  : public ProcessConcurrent
{

public:

  SIFT_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName);
  ~SIFT_KPDescProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvkey;
  cv::Mat &mCvDesc;

};

#endif // SIFT_KPDESCPROCESS_H
