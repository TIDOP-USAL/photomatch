#include "WallisProcess.h"

#include <opencv2/photo.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

namespace fme
{

WallisProcess::WallisProcess()
  : ProcessConcurrent(),
    IWallis(),
    mImgInput(""),
    mImgOutput(""),
    mContrast(1.0),
    mBrightness(0.2),
    mImposedAverage(41),
    mImposedLocalStdDev(127),
    mKernelSize(50)
{

}

WallisProcess::WallisProcess(const QString &imgInput,
                             const QString &imgOutput,
                             double contrast,
                             double brightness,
                             int imposedAverage,
                             int imposedLocalStdDev,
                             int kernelSize)
  : ProcessConcurrent(),
    IWallis(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mContrast(contrast),
    mBrightness(brightness),
    mImposedAverage(imposedAverage),
    mImposedLocalStdDev(imposedLocalStdDev),
    mKernelSize(kernelSize)
{

}

WallisProcess::~WallisProcess()
{

}

double WallisProcess::contrast() const
{
  return mContrast;
}

void WallisProcess::setContrast(double contrast)
{
  mContrast = contrast;
}

double WallisProcess::brightness() const
{
  return mBrightness;
}

void WallisProcess::setBrightness(double brightness)
{
  mBrightness = brightness;
}

int WallisProcess::imposedAverage() const
{
  return mImposedAverage;
}

void WallisProcess::setImposedAverage(int imposedAverage)
{
  mImposedAverage = imposedAverage;
}

int WallisProcess::imposedLocalStdDev() const
{
  return mImposedLocalStdDev;
}

void WallisProcess::setImposedLocalStdDev(int imposedLocalStdDev)
{
  mImposedLocalStdDev = imposedLocalStdDev;
}

int WallisProcess::kernelSize() const
{
  return mKernelSize;
}

void WallisProcess::setKernelSize(int kernelSize)
{
  mKernelSize = kernelSize;
}

void WallisProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mContrast = 1.0;
  mBrightness = 0.2;
  mImposedAverage = 41;
  mImposedLocalStdDev = 127;
  mKernelSize = 50;
}

void WallisProcess::run()
{
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();
  cv::Mat img = cv::imread(input_img);

  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, img, color_boost);
  }

  img.convertTo(img, CV_32F);

  cv::Mat localMean;
  cv::blur(img, localMean, Size(mKernelSize, mKernelSize)); //Easier to compute this way
  cv::Mat differentialImage;
  cv::blur(img.mul(img), differentialImage, Size(mKernelSize, mKernelSize));
  cv::Mat localStandardDeviation;
  cv::sqrt(differentialImage - localMean.mul(localMean), localStandardDeviation);

  cv::Mat r1 = static_cast<double>(mContrast * mImposedLocalStdDev)
               / (localStandardDeviation + (1. - static_cast<double>(mContrast)));
  cv::Mat r0 = static_cast<double>(mBrightness * mImposedAverage)
               + localMean.mul(1. - static_cast<double>(mBrightness) - r1);
  cv::Mat out = img.mul(r1) + r0;

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);
}

} // namespace fme
