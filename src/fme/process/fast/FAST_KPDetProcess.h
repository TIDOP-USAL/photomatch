#ifndef FME_FAST_KPDETPROCESS_H
#define FME_FAST_KPDETPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT FAST_KPDetProcess
  : public ProcessConcurrent
{
public:

  FAST_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName);
  ~FAST_KPDetProcess();

  void run();

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvKey;

};

#endif // FME_FAST_KPDETPROCESS_H
