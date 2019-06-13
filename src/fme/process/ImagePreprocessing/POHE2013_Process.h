#ifndef FME_POHE2013_PROCESS_H
#define FME_POHE2013_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT POHE2013_Process
  : public ProcessConcurrent
{

public:

  POHE2013_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const QDir &outputDir);
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  QDir mOutputDir;

};

#endif // FME_POHE2013_PROCESS_H
