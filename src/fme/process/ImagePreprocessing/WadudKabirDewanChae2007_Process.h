#ifndef WADUDKABIRDEWANCHAE2007_PROCESS_H
#define WADUDKABIRDEWANCHAE2007_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT WadudKabirDewanChae2007_Process
  : public ProcessConcurrent
{

public:

  WadudKabirDewanChae2007_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, int power, const QDir &outputDir);
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  int mPower;
  QDir mOutputDir;

};

#endif // WADUDKABIRDEWANCHAE2007_PROCESS_H
