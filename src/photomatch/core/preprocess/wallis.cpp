#include "wallis.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{



WallisProperties::WallisProperties()
  : IWallis(),
    mContrast(1.0),
    mBrightness(0.2),
    mImposedAverage(41),
    mImposedLocalStdDev(127),
    mKernelSize(50)
{

}

WallisProperties::~WallisProperties()
{
}

double WallisProperties::contrast() const
{
  return mContrast;
}

void WallisProperties::setContrast(double contrast)
{
  mContrast = contrast;
}

double WallisProperties::brightness() const
{
  return mBrightness;
}

void WallisProperties::setBrightness(double brightness)
{
  mBrightness = brightness;
}

int WallisProperties::imposedAverage() const
{
  return mImposedAverage;
}

void WallisProperties::setImposedAverage(int imposedAverage)
{
  mImposedAverage = imposedAverage;
}

int WallisProperties::imposedLocalStdDev() const
{
  return mImposedLocalStdDev;
}

void WallisProperties::setImposedLocalStdDev(int imposedLocalStdDev)
{
  mImposedLocalStdDev = imposedLocalStdDev;
}

int WallisProperties::kernelSize() const
{
  return mKernelSize;
}

void WallisProperties::setKernelSize(int kernelSize)
{
  mKernelSize = kernelSize;
}

void WallisProperties::reset()
{
  mContrast = 1.0;
  mBrightness = 0.2;
  mImposedAverage = 41;
  mImposedLocalStdDev = 127;
  mKernelSize = 50;
}

QString WallisProperties::name() const
{
  return QString("WALLIS");
}


/*----------------------------------------------------------------*/


WallisPreprocess::WallisPreprocess()
  : WallisProperties(),
    ImageProcess()
{
}

WallisPreprocess::WallisPreprocess(double contrast,
                                   double brightness,
                                   int imposedAverage,
                                   int imposedLocalStdDev,
                                   int kernelSize)
  : WallisProperties(),
    ImageProcess()
{
  this->setContrast(contrast);
  this->setBrightness(brightness);
  this->setImposedAverage(imposedAverage);
  this->setImposedLocalStdDev(imposedLocalStdDev);
  this->setKernelSize(kernelSize);
}

WallisPreprocess::~WallisPreprocess()
{

}

cv::Mat WallisPreprocess::process(const cv::Mat &img)
{
  cv::Mat color_boost;
  cv::Mat temp;
  if (img.channels() >= 3) {
    cv::decolor(img, temp, color_boost);
    color_boost.release();
  } else {
    img.copyTo(temp);
  }

  temp.convertTo(temp, CV_32F);

  cv::Mat localMean;
  cv::blur(temp, localMean, cv::Size(WallisProperties::kernelSize(), WallisProperties::kernelSize())); //Easier to compute this way
  cv::Mat differentialImage;
  cv::blur(temp.mul(temp), differentialImage, cv::Size(WallisProperties::kernelSize(), WallisProperties::kernelSize()));
  cv::Mat localStandardDeviation;
  cv::sqrt(differentialImage - localMean.mul(localMean), localStandardDeviation);
  differentialImage.release();

  cv::Mat r1 = static_cast<double>(WallisProperties::contrast() * WallisProperties::imposedLocalStdDev())
               / (localStandardDeviation + (1. - static_cast<double>(WallisProperties::contrast())));
  localStandardDeviation.release();
  cv::Mat r0 = static_cast<double>(WallisProperties::brightness() * WallisProperties::imposedAverage())
               + localMean.mul(1. - static_cast<double>(WallisProperties::brightness()) - r1);
  localMean.release();
  cv::Mat out = temp.mul(r1) + r0;
  temp.release();
  r0.release();
  r1.release();

  return out;
}


} // namespace photomatch







