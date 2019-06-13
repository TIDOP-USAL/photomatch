#ifndef FME_BRISK_KPDETPROCESS_H
#define FME_BRISK_KPDETPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT BRISK_KPDetProcess
  : public ProcessConcurrent
{

public:

  BRISK_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName);
  ~BRISK_KPDetProcess() override;

  virtual void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvKey;

};

#endif // FME_BRISK_KPDETPROCESS_H
