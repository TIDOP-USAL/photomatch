#ifndef FME_LIUJINCHENLIULI2011_PROCESS_H
#define FME_LIUJINCHENLIULI2011_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"


class FME_EXPORT LiuJinChenLiuLi2011_Process
  : public ProcessConcurrent
{

public:

  LiuJinChenLiuLi2011_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, const QDir &outputDir);
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  QDir mOutputDir;

};

#endif // FME_LIUJINCHENLIULI2011_PROCESS_H
