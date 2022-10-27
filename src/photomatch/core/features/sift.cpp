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


#include "sift.h"

#include <tidop/core/messages.h>


namespace photomatch
{


SiftProperties::SiftProperties()
  : mFeaturesNumber(5000),
    mOctaveLayers(3),
    mContrastThreshold(0.04),
    mEdgeThreshold(10.),
    mSigma(1.6)
{
}

SiftProperties::SiftProperties(const SiftProperties &siftProperties)
  : Sift(siftProperties),
    mFeaturesNumber(siftProperties.mFeaturesNumber),
    mOctaveLayers(siftProperties.mOctaveLayers),
    mContrastThreshold(siftProperties.mContrastThreshold),
    mEdgeThreshold(siftProperties.mEdgeThreshold),
    mSigma(siftProperties.mSigma)
{
}

int SiftProperties::featuresNumber() const
{
  return mFeaturesNumber;
}

int SiftProperties::octaveLayers() const
{
  return mOctaveLayers;
}

double SiftProperties::contrastThreshold() const
{
  return mContrastThreshold;
}

double SiftProperties::edgeThreshold() const
{
  return mEdgeThreshold;
}

double SiftProperties::sigma() const
{
  return mSigma;
}

void SiftProperties::setFeaturesNumber(int featuresNumber)
{
  mFeaturesNumber = featuresNumber;
}

void SiftProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void SiftProperties::setContrastThreshold(double contrastThreshold)
{
  mContrastThreshold = contrastThreshold;
}

void SiftProperties::setEdgeThreshold(double edgeThreshold)
{
  mEdgeThreshold = edgeThreshold;
}

void SiftProperties::setSigma(double sigma)
{
  mSigma = sigma;
}

void SiftProperties::reset()
{
  mFeaturesNumber = 5000;
  mOctaveLayers = 3;
  mContrastThreshold = 0.04;
  mEdgeThreshold = 10.;
  mSigma = 1.6;
}

QString SiftProperties::name() const
{
  return QString("SIFT");
}


/*----------------------------------------------------------------*/


SiftDetectorDescriptor::SiftDetectorDescriptor()
{ 
  update();
}

SiftDetectorDescriptor::SiftDetectorDescriptor(const SiftDetectorDescriptor &siftDetectorDescriptor)
  : SiftProperties(siftDetectorDescriptor),
    KeypointDetector(siftDetectorDescriptor),
    DescriptorExtractor(siftDetectorDescriptor)
{
  update();
}

SiftDetectorDescriptor::SiftDetectorDescriptor(int featuresNumber,
                                               int octaveLayers,
                                               double contrastThreshold,
                                               double edgeThreshold,
                                               double sigma)
{
  SiftProperties::setFeaturesNumber(featuresNumber);
  SiftProperties::setOctaveLayers(octaveLayers);
  SiftProperties::setContrastThreshold(contrastThreshold);
  SiftProperties::setEdgeThreshold(edgeThreshold);
  SiftProperties::setSigma(sigma);
  update();
}

void SiftDetectorDescriptor::update()
{
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4))
  mSift = cv::SIFT::create(SiftProperties::featuresNumber(),
                           SiftProperties::octaveLayers(),
                           SiftProperties::contrastThreshold(),
                           SiftProperties::edgeThreshold(),
                           SiftProperties::sigma());
#elif defined HAVE_OPENCV_XFEATURES2D && defined OPENCV_ENABLE_NONFREE
  mSift = cv::xfeatures2d::SIFT::create(SiftProperties::featuresNumber(),
                                        SiftProperties::octaveLayers(),
                                        SiftProperties::contrastThreshold(),
                                        SiftProperties::edgeThreshold(),
                                        SiftProperties::sigma());
#endif
}

std::vector<cv::KeyPoint> SiftDetectorDescriptor::detect(const cv::Mat &img, 
                                                         const cv::Mat &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mSift->detect(img, keyPoints, mask);
  return keyPoints;
}

cv::Mat SiftDetectorDescriptor::extract(const cv::Mat &img, 
                                        std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mSift->compute(img, keyPoints, descriptors);
  return descriptors;
}

void SiftDetectorDescriptor::setFeaturesNumber(int featuresNumber)
{
  SiftProperties::setFeaturesNumber(featuresNumber);
  update();
}

void SiftDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  SiftProperties::setOctaveLayers(octaveLayers);
  update();
}

void SiftDetectorDescriptor::setContrastThreshold(double contrastThreshold)
{
  SiftProperties::setContrastThreshold(contrastThreshold);
  update();
}

void SiftDetectorDescriptor::setEdgeThreshold(double edgeThreshold)
{
  SiftProperties::setEdgeThreshold(edgeThreshold);
  update();
}

void SiftDetectorDescriptor::setSigma(double sigma)
{
  SiftProperties::setSigma(sigma);
  update();
}

void SiftDetectorDescriptor::reset()
{
  SiftProperties::reset();
  update();
}


} // namespace photomatch







