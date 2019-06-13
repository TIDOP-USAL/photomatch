#ifndef FME_MARYKIM2008_PROCESS_H
#define FME_MARYKIM2008_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT MaryKim2008_Process
  : public ProcessConcurrent
{
public:

  MaryKim2008_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, int morD, int r, const QDir &outputDir);

  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  int mMorD;
  int mR;
  QDir mOutputDir;

};

#endif // FME_MARYKIM2008_PROCESS_H
