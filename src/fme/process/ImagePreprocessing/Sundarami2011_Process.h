#ifndef SUNDARAMI2011_PROCESS_H
#define SUNDARAMI2011_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT Sundarami2011_Process
  : public ProcessConcurrent
{

public:

  Sundarami2011_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, float L, float phi, const QDir &outputDir);
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  float mL;
  float mPhi;
  QDir mOutputDir;

};

#endif // SUNDARAMI2011_PROCESS_H
