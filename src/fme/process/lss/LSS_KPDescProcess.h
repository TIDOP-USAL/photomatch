#ifndef FME_LSS_KPDETPROCESS_H
#define FME_LSS_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT LSS_KPDescProcess
  : public ProcessConcurrent
{

public:

  LSS_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey, cv::Mat &cvDesc, const QString &imageName);
  ~LSS_KPDescProcess() override;
  
  void run() override;

private:

  QString mImageName;
  cv::Mat &mCvImg;
  std::vector<cv::KeyPoint> &mCvkey;
  cv::Mat &mCvDesc;

};

#endif // FME_LSS_KPDETPROCESS_H
