#ifndef MTM_KPDESCPROCESS_H
#define MTM_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

using namespace cv;

class FME_EXPORT MTM_KPDescProcess : public ProcessConcurrent
{
public:

  MTM_KPDescProcess(cv::Mat &cvImgLeft, cv::Mat &cvImgRight, std::vector<cv::KeyPoint> &cvkeyLeft, std::vector<cv::KeyPoint> &cvkeyRight, std::vector<std::vector<cv::DMatch>> &matchesL2R, std::vector<std::vector<cv::DMatch>> &matchesR2L, int sizePatch, int nBins, const QString &leftImageName, const QString &rightImageName);
  ~MTM_KPDescProcess() override;

  void run() override;

private:

  void normalizepatch(int i, cv::Mat &output, int leftorright);

private:

  QString mLeftImageName, mRightImageName;
  cv::Mat &mCvImgLeft, &mCvImgRight;
  std::vector<cv::KeyPoint> &mCvkeyLeft, &mCvkeyRight;
  std::vector<std::vector<cv::DMatch>> &mMatchesL2R, &mMatchesR2L;
  int mSizePatch, mNBins;

};

#endif // MTM_KPDescProcess_H
