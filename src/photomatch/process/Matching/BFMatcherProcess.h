#ifndef PHOTOMATCH_BFMATCHER_PROCESS_H
#define PHOTOMATCH_BFMATCHER_PROCESS_H

#include <opencv2/core.hpp>

#include "photomatch/process/ProcessConcurrent.h"

class PHOTOMATCH_EXPORT BFMatcherProcess
  : public ProcessConcurrent
{
public:

  BFMatcherProcess(cv::Mat &cvDescLeft, cv::Mat &cvDescRight, std::vector<std::vector<cv::DMatch>> &matchesL2R, std::vector<std::vector<cv::DMatch>> &matchesR2L, const QString &leftImageName, const QString &rightImageName);
  ~BFMatcherProcess() override;

  void run() override;

private:

  QString mLeftImageName, mRightImageName;
  cv::Mat &mCvDescLeft, &mCvDescRight;
  std::vector<std::vector<cv::DMatch>> &mCvMatchesL2R, &mCvMatchesR2L;

};

#endif // PHOTOMATCH_BFMATCHER_PROCESS_H
