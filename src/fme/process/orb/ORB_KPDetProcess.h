#ifndef FME_ORB_KPDETPROCESS_H
#define FME_ORB_KPDETPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT ORB_KPDetProcess
  : public ProcessConcurrent
{

public:

  ORB_KPDetProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvKey, int maxFeatures, const QString &imageName);
  ~ORB_KPDetProcess() override;

  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  int mMaxFeatures;
  std::vector<cv::KeyPoint> &mCvKey;

};

#endif // FME_ORB_KPDETPROCESS_H
