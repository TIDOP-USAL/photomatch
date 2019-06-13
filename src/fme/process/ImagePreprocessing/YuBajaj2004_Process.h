#ifndef YUBAJAJ2004_PROCESS_H
#define YUBAJAJ2004_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT YuBajaj2004_Process
  : public ProcessConcurrent
{

public:

  YuBajaj2004_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, float c, bool anisotropicMode, float r, const QDir &outputDir);
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  float mC;
  bool mAnisotropicMode;
  float mR;
  QDir mOutputDir;

};

#endif // YUBAJAJ2004_PROCESS_H
