#ifndef FME_MSER_KPDETPROCESS_H
#define FME_MSER_KPDETPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT MSER_KPDetProcess : public ProcessConcurrent
{
public:

  MSER_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, const QString &imageName);
  ~MSER_KPDetProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvKey;

};

#endif // FME_MSER_KPDETPROCESS_H
