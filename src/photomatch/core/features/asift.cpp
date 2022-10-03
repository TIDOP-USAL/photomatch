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


#include "asift.h"

#include <tidop/core/messages.h>


namespace photomatch
{


ASiftProperties::ASiftProperties()
  : mFeaturesNumber(5000),
    mOctaveLayers(3),
    mContrastThreshold(0.04),
    mEdgeThreshold(10.),
    mSigma(1.6),
    mMinTilt(0),
    mMaxTilt(1)
{
}

ASiftProperties::ASiftProperties(const ASiftProperties &asiftProperties)
  : ASift(asiftProperties),
    mFeaturesNumber(asiftProperties.mFeaturesNumber),
    mOctaveLayers(asiftProperties.mOctaveLayers),
    mContrastThreshold(asiftProperties.mContrastThreshold),
    mEdgeThreshold(asiftProperties.mEdgeThreshold),
    mSigma(asiftProperties.mSigma),
    mMinTilt(asiftProperties.mMinTilt),
    mMaxTilt(asiftProperties.mMaxTilt)
{
}

int ASiftProperties::featuresNumber() const
{
  return mFeaturesNumber;
}

int ASiftProperties::octaveLayers() const
{
  return mOctaveLayers;
}

double ASiftProperties::contrastThreshold() const
{
  return mContrastThreshold;
}

double ASiftProperties::edgeThreshold() const
{
  return mEdgeThreshold;
}

double ASiftProperties::sigma() const
{
  return mSigma;
}

void ASiftProperties::setFeaturesNumber(int featuresNumber)
{
  mFeaturesNumber = featuresNumber;
}

void ASiftProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void ASiftProperties::setContrastThreshold(double contrastThreshold)
{
  mContrastThreshold = contrastThreshold;
}

void ASiftProperties::setEdgeThreshold(double edgeThreshold)
{
  mEdgeThreshold = edgeThreshold;
}

void ASiftProperties::setSigma(double sigma)
{
  mSigma = sigma;
}

int ASiftProperties::minTilt() const
{
  return mMinTilt;
}

int ASiftProperties::maxTilt() const
{
  return mMaxTilt;
}

void ASiftProperties::setMinTilt(int minTilt)
{
  mMinTilt = minTilt;
}

void ASiftProperties::setMaxTilt(int maxTilt)
{
  mMaxTilt = maxTilt;
}

void ASiftProperties::reset()
{
  mFeaturesNumber = 5000;
  mOctaveLayers = 3;
  mContrastThreshold = 0.04;
  mEdgeThreshold = 10.;
  mSigma = 1.6;
  mMinTilt = 0;
  mMaxTilt = 1;
}

QString ASiftProperties::name() const
{
  return QString("ASIFT");
}


/*----------------------------------------------------------------*/

#if (CV_VERSION_MAJOR > 4 || CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4) || defined OPENCV_ENABLE_NONFREE

ASiftDetectorDescriptor::ASiftDetectorDescriptor()
{ 
  update();
}

ASiftDetectorDescriptor::ASiftDetectorDescriptor(const ASiftDetectorDescriptor &asiftDetectorDescriptor)
  : ASiftProperties(asiftDetectorDescriptor),
    KeypointDetector(asiftDetectorDescriptor),
    DescriptorExtractor(asiftDetectorDescriptor)
{
  update();
}

ASiftDetectorDescriptor::ASiftDetectorDescriptor(int featuresNumber,
                                                 int octaveLayers,
                                                 double contrastThreshold,
                                                 double edgeThreshold,
                                                 double sigma,
                                                 int minTilt,
                                                 int maxTilt)
{
  ASiftProperties::setFeaturesNumber(featuresNumber);
  ASiftProperties::setOctaveLayers(octaveLayers);
  ASiftProperties::setContrastThreshold(contrastThreshold);
  ASiftProperties::setEdgeThreshold(edgeThreshold);
  ASiftProperties::setSigma(sigma);
  ASiftProperties::setMinTilt(minTilt);
  ASiftProperties::setMaxTilt(maxTilt);

  update();
}

void ASiftDetectorDescriptor::update()
{
  cv::Ptr<cv::FeatureDetector> sift = cv::xfeatures2d::SIFT::create(ASiftProperties::featuresNumber(),
                                                                    ASiftProperties::octaveLayers(),
                                                                    ASiftProperties::contrastThreshold(),
                                                                    ASiftProperties::edgeThreshold(),
                                                                    ASiftProperties::sigma());
  cv::Ptr<cv::affma::AffAngles> angles = cv::affma::createAffAngles(ASiftProperties::maxTilt(), ASiftProperties::minTilt());

  mDetector = cv::affma::createAffFeatureDetector(sift, angles); 
  mDescriptor = cv::affma::createAffDescriptorExtractor(sift, ASiftProperties::maxTilt());                                    
}

std::vector<cv::KeyPoint> ASiftDetectorDescriptor::detect(const cv::Mat &img, 
                                                          const cv::Mat &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mDetector->detect(img, keyPoints, mask);
  return keyPoints;
}

cv::Mat ASiftDetectorDescriptor::extract(const cv::Mat &img, 
                                         std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mDescriptor->compute(img, keyPoints, descriptors);
  return descriptors;
}

void ASiftDetectorDescriptor::setFeaturesNumber(int featuresNumber)
{
  ASiftProperties::setFeaturesNumber(featuresNumber);
  update();
}

void ASiftDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  ASiftProperties::setOctaveLayers(octaveLayers);
  update();
}

void ASiftDetectorDescriptor::setContrastThreshold(double contrastThreshold)
{
  ASiftProperties::setContrastThreshold(contrastThreshold);
  update();
}

void ASiftDetectorDescriptor::setEdgeThreshold(double edgeThreshold)
{
  ASiftProperties::setEdgeThreshold(edgeThreshold);
  update();
}

void ASiftDetectorDescriptor::setSigma(double sigma)
{
  ASiftProperties::setSigma(sigma);
  update();
}

void ASiftDetectorDescriptor::setMinTilt(int minTilt)
{
  ASiftProperties::setSigma(minTilt);
  update();
}

void ASiftDetectorDescriptor::setMaxTilt(int maxTilt)
{
  ASiftProperties::setSigma(maxTilt);
  update();
}

void ASiftDetectorDescriptor::reset()
{
  ASiftProperties::reset();
  update();
}

#endif


} // namespace photomatch







