#ifndef FME_GFTT_KPDETPROCESS_H
#define FME_GFTT_KPDETPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT GFTT_KPDetProcess
  : public ProcessConcurrent
{

public:

  GFTT_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName);
  ~GFTT_KPDetProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvKey;

};

#endif // FME_GFTT_KPDETPROCESS_H
