#ifndef WRITEMATCHESTOAPEROPROCESS_H
#define WRITEMATCHESTOAPEROPROCESS_H

#include <opencv2/core.hpp>

#include "photomatch/process/ProcessConcurrent.h"

class PHOTOMATCH_EXPORT WriteMatchesToAperoProcess
  : public ProcessConcurrent
{

public:

  WriteMatchesToAperoProcess(QString filename, std::vector<cv::KeyPoint> &cvkeyLeft, std::vector<cv::KeyPoint> &cvkeyRight, std::vector<cv::DMatch> &cvMatches);
  ~WriteMatchesToAperoProcess() override;

  void run() override;

private:
  
  QString mFileName;
  std::vector<cv::DMatch> &mCvMatches;
  std::vector<cv::KeyPoint> &mCvKeyLeft, &mCvKeyRight;

};

#endif // WRITEMATCHESTOAPEROPROCESS_H
