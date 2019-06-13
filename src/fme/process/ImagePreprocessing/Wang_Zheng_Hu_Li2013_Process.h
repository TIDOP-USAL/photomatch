#ifndef WANG_ZHENG_HU_LI2013_PROCESS_H
#define WANG_ZHENG_HU_LI2013_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT Wang_Zheng_Hu_Li2013_Process
  : public ProcessConcurrent
{
public:
  Wang_Zheng_Hu_Li2013_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const QDir &outputDir);
  virtual void run() override;

private:
  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  QDir mOutputDir;
};

#endif // WANG_ZHENG_HU_LI2013_PROCESS_H
