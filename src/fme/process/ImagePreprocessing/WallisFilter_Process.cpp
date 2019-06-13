#include "WallisFilter_Process.h"

#include <opencv2/photo.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

WallisFilter_Process::WallisFilter_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, float contrast, float brightness, int imposedAverage, int imposedLocalStandardDeviation, int kernelSize, const QDir &outputDir) 
  : mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mOutputDir(outputDir),
    mContrast(contrast),
    mBrightness(brightness),
    mImposedAverage(imposedAverage),
    mImposedLocalStandardDeviation(imposedLocalStandardDeviation),
    mKernelSize(kernelSize)
{

}

void WallisFilter_Process::run()
{

  cv::Mat color_boost;
  if (mCvImg_left.channels() >= 3) {
    cv::decolor(mCvImg_left, mCvImg_left, color_boost);
  }
  if (mCvImg_right.channels() >= 3) {
    cv::decolor(mCvImg_right, mCvImg_right, color_boost);
  }

  mCvImg_left.convertTo(mCvImg_left, CV_32F);

  cv::Mat localMean;
  cv::blur(mCvImg_left, localMean, Size(mKernelSize, mKernelSize)); //Easier to compute this way
  cv::Mat differentialImage;
  cv::blur(mCvImg_left.mul(mCvImg_left), differentialImage, Size(mKernelSize, mKernelSize));
  cv::Mat localStandardDeviation;
  cv::sqrt(differentialImage - localMean.mul(localMean), localStandardDeviation);

  cv::Mat r1 = static_cast<double>(mContrast * mImposedLocalStandardDeviation)
    / (localStandardDeviation + (1. - static_cast<double>(mContrast)));
  cv::Mat r0 = static_cast<double>(mBrightness * mImposedAverage)
    + localMean.mul(1. - static_cast<double>(mBrightness) - r1);
  mCvImg_left = mCvImg_left.mul(r1) + r0;

  mCvImg_right.convertTo(mCvImg_right, CV_32F);


  cv::blur(mCvImg_right, localMean, Size(mKernelSize, mKernelSize)); //Easier to compute this way
  cv::blur(mCvImg_right.mul(mCvImg_right), differentialImage, Size(mKernelSize, mKernelSize));
  cv::sqrt(differentialImage - localMean.mul(localMean), localStandardDeviation);


  r1 = static_cast<double>(mContrast * mImposedLocalStandardDeviation)
    / (localStandardDeviation + (1. - static_cast<double>(mContrast)));
  r0 = static_cast<double>(mBrightness * mImposedAverage)
    + localMean.mul(1. - static_cast<double>(mBrightness) - r1);
  mCvImg_right = mCvImg_right.mul(r1) + r0;


  cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
  cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
