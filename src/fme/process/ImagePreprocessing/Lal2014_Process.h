#ifndef FME_LAL2014_PROCESS_H
#define FME_LAL2014_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include <opencv/cv.h>
#include <QDir>

class FME_EXPORT Lal2014_Process
  : public ProcessConcurrent
{

public:

  Lal2014_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, const QDir &outputDir);

  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  QDir mOutputDir;
};

#endif // FME_LAL2014_PROCESS_H
