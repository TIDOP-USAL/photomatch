#ifndef SURF_KPDETPROCESS_H
#define SURF_KPDETPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT SURF_KPDetProcess
  : public ProcessConcurrent
{

public:

  SURF_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName);
  ~SURF_KPDetProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvKey;

};

#endif // SURF_KPDETPROCESS_H
