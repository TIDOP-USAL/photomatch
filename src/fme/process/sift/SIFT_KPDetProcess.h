#ifndef SIFT_KPDETPROCESS_H
#define SIFT_KPDETPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT SIFT_KPDetProcess
  : public ProcessConcurrent
{

public:

  SIFT_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName);
  ~SIFT_KPDetProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvKey;

};

#endif // SIFT_KPDETPROCESS_H
