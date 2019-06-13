#ifndef FME_HOG_KPDESCPROCESS_H
#define FME_HOG_KPDESCPROCESS_H

#include <opencv2/core.hpp>

#include "fme/process/ProcessConcurrent.h"

class FME_EXPORT HOG_KPDescProcess
  : public ProcessConcurrent
{
public:

  HOG_KPDescProcess(cv::Mat &cvImgLeft, cv::Mat &cvImgRight, 
                    std::vector<cv::KeyPoint> &cvkeyLeft, 
                    std::vector<cv::KeyPoint> &cvkeyRight, 
                    cv::Mat &cvDescLeft, cv::Mat &cvDescRight, 
                    int sizePatch, const QString &leftImageName, 
                    const QString &rightImageName);
  ~HOG_KPDescProcess() override;

  void run() override;

private:
  
  void normalizepatch(int i, cv::Mat &output, int leftorright);

private:

  QString mLeftImageName, mRightImageName;
  cv::Mat &mCvImgLeft, &mCvImgRight;
  std::vector<cv::KeyPoint> &mCvkeyLeft, &mCvkeyRight;
  cv::Mat &mCvDescLeft, &mCvDescRight;
  int mSizePatch;

};

#endif // FME_HOG_KPDESCPROCESS_H
