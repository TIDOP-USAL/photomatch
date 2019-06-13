#ifndef FME_CELIKTJAHJADI2012_PROCESS_H
#define FME_CELIKTJAHJADI2012_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT CelikTjahjadi2012_Process
  : public ProcessConcurrent
{

public:

  CelikTjahjadi2012_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, int n, const QDir &outputDir);
  virtual void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  int mN;
  QDir mOutputDir;
};

#endif // FME_CELIKTJAHJADI2012_PROCESS_H
