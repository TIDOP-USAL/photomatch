#ifndef ROBUSTMATCHERREFINEMENTPROCESS_H
#define ROBUSTMATCHERREFINEMENTPROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT RobustMatcherRefinementProcess
  : public ProcessConcurrent
{

public:

  RobustMatcherRefinementProcess(cv::Mat &cvImgLeft, cv::Mat &cvImgRight, std::vector<cv::KeyPoint> &cvkeyLeft, std::vector<cv::KeyPoint> &cvkeyRight, std::vector<std::vector<cv::DMatch>> &matchesL2R, std::vector<std::vector<cv::DMatch>> &matchesR2L, std::vector<cv::DMatch> &correctMatches, std::vector<cv::DMatch> &wrongMatches, int refinementMethod, float k, float ratio, float distance, float confidence, bool fromMI, bool haveGroundTruth, cv::Mat &groundTruth, const QString &leftImageName, const QString &rightImageName, const QDir &outputHomographyDir);
  ~RobustMatcherRefinementProcess() override;

  void run() override;

private:

  QString mLeftImageName, mRightImageName;
  cv::Mat &mCvImgLeft, &mCvImgRight;
  std::vector<cv::KeyPoint> &mCvKeyLeft, &mCvKeyRight;
  std::vector<std::vector<cv::DMatch>> &mCvMatchesL2R, &mCvMatchesR2L;
  std::vector<cv::DMatch> &mCvCorrectMatches, &mCvWrongMatches;
  float mK, mRatio, mDistance, mConfidence;
  int mRefinementMethod;
  bool mFromMI, mHaveGroundTruth;
  cv::Mat &mGroundTruth;
  QDir mOutputHomographyDir;

};

#endif // ROBUSTMATCHERREFINEMENTPROCESS_H
