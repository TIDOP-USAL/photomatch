#ifndef FME_LAMBERTIMONTRUCCHIOSANNA2006_PROCESS_H
#define FME_LAMBERTIMONTRUCCHIOSANNA2006_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT LambertiMontrucchioSanna2006_Process
  : public ProcessConcurrent
{

public:

  LambertiMontrucchioSanna2006_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, 
                                       const cv::Size &blockSize, const cv::Size &blockRegions, 
                                       const QDir &outputDir);
  
  void run() override;

private:

  cv::Mat& mCvImg_left;
  cv::Mat& mCvImg_right;
  cv::Size mBlockSize;
  cv::Size mBlockRegions;
  QDir mOutputDir;

};

#endif // FME_LAMBERTIMONTRUCCHIOSANNA2006_PROCESS_H
