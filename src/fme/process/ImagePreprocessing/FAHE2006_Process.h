#ifndef FME_FAHE2006_PROCESS_H
#define FME_FAHE2006_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT FAHE2006_Process
  : public ProcessConcurrent
{

public:

  FAHE2006_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, const QDir &outputDir);

  virtual void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  QDir mOutputDir;

};

#endif // FME_FAHE2006_PROCESS_H
