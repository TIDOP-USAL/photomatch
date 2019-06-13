#ifndef WALLISFILTER_PROCESS_H
#define WALLISFILTER_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT WallisFilter_Process
  : public ProcessConcurrent
{

public:

  WallisFilter_Process(cv::Mat& cvImg_Left, cv::Mat& cvImg_Right, float contrast, float brightness, int imposedAverage, int imposedLocalStandardDeviation, int kernelSize, const QDir &outputDir);
  virtual void run();

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  QDir mOutputDir;

  float mContrast;
  float mBrightness;
  int mImposedAverage;
  int mImposedLocalStandardDeviation;
  int mKernelSize;

};

#endif // WALLISFILTER_PROCESS_H
