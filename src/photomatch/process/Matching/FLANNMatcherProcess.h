#ifndef PHOTOMATCH_FLANNMATCHERPROCESS_H
#define PHOTOMATCH_FLANNMATCHERPROCESS_H

#include <opencv2/core.hpp>

#include "photomatch/process/ProcessConcurrent.h"

class PHOTOMATCH_EXPORT FLANNMatcherProcess
  : public ProcessConcurrent
{

public:

  FLANNMatcherProcess(cv::Mat &cvImgLeft, cv::Mat &cvImgRight, 
                      std::vector<cv::KeyPoint> &cvkeyLeft, 
                      std::vector<cv::KeyPoint> &cvkeyRight, 
                      cv::Mat &cvDescLeft, cv::Mat &cvDescRight, 
                      std::vector<cv::DMatch> &correctMatches, 
                      std::vector<cv::DMatch> &wrongMatches, 
                      bool haveGroundTruth, cv::Mat &groundTruth, 
                      const QString &leftImageName, const QString &rightImageName);
  ~FLANNMatcherProcess();

  void run();

private:

  QString mLeftImageName, mRightImageName;
  cv::Mat &mCvImgLeft, &mCvImgRight;
  std::vector<cv::KeyPoint> &mCvKeyLeft, &mCvKeyRight;
  cv::Mat &mCvDescLeft, &mCvDescRight;
  std::vector<cv::DMatch> &mCorrectMatches, &mWrongMatches;
  bool mHaveGroundTruth;
  cv::Mat &mGroundTruth;

};

#endif // PHOTOMATCH_FLANNMATCHERPROCESS_H
