#ifndef RAJUNAIR2014_PROCESS_H
#define RAJUNAIR2014_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT RajuNair2014_Process
  : public ProcessConcurrent
{

public:

  RajuNair2014_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const QDir &outputDir);
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  QDir mOutputDir;

};

#endif // RAJUNAIR2014_PROCESS_H
