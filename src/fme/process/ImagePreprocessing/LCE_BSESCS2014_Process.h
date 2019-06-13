#ifndef FME_LCE_BSESCS2014_PROCESS_H
#define FME_LCE_BSESCS2014_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT LCE_BSESCS2014_Process
  : public ProcessConcurrent
{

public:

  LCE_BSESCS2014_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, const QDir &outputDir);
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  QDir mOutputDir;
};

#endif // FME_LCE_BSESCS2014_PROCESS_H
