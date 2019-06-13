#ifndef FME_KIMORI2013_PROCESS_H
#define FME_KIMORI2013_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT Kimori2013_Process
  : public ProcessConcurrent
{

public:

  Kimori2013_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, const QDir &outputDir);

  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  QDir mOutputDir;

};

#endif // FME_KIMORI2013_PROCESS_H
