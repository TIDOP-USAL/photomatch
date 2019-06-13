#ifndef FME_CONTRAST_PRESERVING_DECOLORIZATION_PROCESS_H
#define FME_CONTRAST_PRESERVING_DECOLORIZATION_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"


class FME_EXPORT ContrastPreservingDecolorization__Process
  : public ProcessConcurrent
{

public:

  ContrastPreservingDecolorization__Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const QDir &outputDir);
  
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  QDir mOutputDir;
};

#endif // FME_CONTRAST_PRESERVING_DECOLORIZATION_PROCESS_H
