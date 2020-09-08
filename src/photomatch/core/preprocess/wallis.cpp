/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "wallis.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{



WallisProperties::WallisProperties()
  : Wallis(),
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

cv::Mat WallisPreprocess::convertToGray32F(const cv::Mat &imageGray)
{
  cv::Mat imageGray32F;
  imageGray.convertTo(imageGray32F, CV_32F);
  return imageGray32F;
}

cv::Mat WallisPreprocess::process(const cv::Mat &imgIn)
{

  cv::Mat imgOut;

  cv::Mat imageGray = convertToGray(imgIn);
  cv::Mat imageGray32F = convertToGray32F(imageGray);
  imageGray.release();

  cv::Mat localMean;
  cv::Size kernelSize(WallisProperties::kernelSize(), WallisProperties::kernelSize());
  cv::blur(imageGray32F, localMean, kernelSize); //Easier to compute this way
  cv::Mat differentialImage;
  cv::blur(imageGray32F.mul(imageGray32F), differentialImage, kernelSize);
  cv::Mat localStandardDeviation;
  cv::sqrt(differentialImage - localMean.mul(localMean), localStandardDeviation);
  differentialImage.release();

  cv::Mat r1 = static_cast<double>(WallisProperties::contrast() * WallisProperties::imposedLocalStdDev())
    / (localStandardDeviation + (1. - static_cast<double>(WallisProperties::contrast())));
  localStandardDeviation.release();
  cv::Mat r0 = static_cast<double>(WallisProperties::brightness() * WallisProperties::imposedAverage())
    + localMean.mul(1. - static_cast<double>(WallisProperties::brightness()) - r1);
  localMean.release();
  imgOut = imageGray32F.mul(r1) + r0;
  imageGray32F.release();
  r0.release();
  r1.release();

  return imgOut;
}


} // namespace photomatch







