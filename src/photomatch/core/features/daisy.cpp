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


#include "daisy.h"

#include <tidop/core/messages.h>


namespace photomatch
{

DaisyProperties::DaisyProperties()
  : Daisy(),
    mRadius(15.),
    mQRadius(3),
    mQTheta(8),
    mQHist(8),
    mNorm("NRM_NONE"),
    mInterpolation(true),
    mUseOrientation(false)
{}

DaisyProperties::DaisyProperties(const DaisyProperties &daisyProperties)
  : Daisy(),
    mRadius(daisyProperties.mRadius),
    mQRadius(daisyProperties.mQRadius),
    mQTheta(daisyProperties.mQTheta),
    mQHist(daisyProperties.mQHist),
    mNorm(daisyProperties.mNorm),
    mInterpolation(daisyProperties.mInterpolation),
    mUseOrientation(daisyProperties.mUseOrientation)
{}

DaisyProperties::~DaisyProperties()
{

}

double DaisyProperties::radius() const
{
  return mRadius;
}

int DaisyProperties::qRadius() const
{
  return mQRadius;
}

int DaisyProperties::qTheta() const
{
  return mQTheta;
}

int DaisyProperties::qHist() const
{
  return mQHist;
}

QString DaisyProperties::norm() const
{
  return mNorm;
}

bool DaisyProperties::interpolation() const
{
  return mInterpolation;
}

bool DaisyProperties::useOrientation() const
{
  return mUseOrientation;
}

void DaisyProperties::setRadius(double radius)
{
  mRadius = radius;
}

void DaisyProperties::setQRadius(int qRadius)
{
  mQRadius = qRadius;
}

void DaisyProperties::setQTheta(int qTheta)
{
  mQTheta = qTheta;
}

void DaisyProperties::setQHist(int qHist)
{
  mQHist = qHist;
}

void DaisyProperties::setNorm(const QString &norm)
{
  mNorm = norm;
}

void DaisyProperties::setInterpolation(bool interpolation)
{
  mInterpolation = interpolation;
}

void DaisyProperties::setUseOrientation(bool useOrientation)
{
  mUseOrientation = useOrientation;
}

void DaisyProperties::reset()
{
  mRadius = 15.;
  mQRadius = 3;
  mQTheta = 8;
  mQHist = 8;
  mNorm = "NRM_NONE";
  mInterpolation = true;
  mUseOrientation = false;
}

QString DaisyProperties::name() const
{
  return QString("DAISY");
}


/*----------------------------------------------------------------*/


DaisyDescriptor::DaisyDescriptor()
  : DaisyProperties(),
    DescriptorExtractor()
{
  update();
}

DaisyDescriptor::DaisyDescriptor(const DaisyDescriptor &daisyDescriptor)
  : DaisyProperties(daisyDescriptor),
    DescriptorExtractor()
{
  update();
}

DaisyDescriptor::DaisyDescriptor(double radius,
                                 int qRadius,
                                 int qTheta,
                                 int qHist,
                                 QString norm,
                                 bool interpolation,
                                 bool useOrientation)
  : DaisyProperties(),
    DescriptorExtractor()
{
  DaisyProperties::setRadius(radius);
  DaisyProperties::setQRadius(qRadius);
  DaisyProperties::setQTheta(qTheta);
  DaisyProperties::setQHist(qHist);
  DaisyProperties::setNorm(norm);
  DaisyProperties::setInterpolation(interpolation);
  DaisyProperties::setUseOrientation(useOrientation);
  update();
}

DaisyDescriptor::~DaisyDescriptor()
{

}

void DaisyDescriptor::update()
{

#if CV_VERSION_MAJOR >= 4
  cv::xfeatures2d::DAISY::NormalizationType daisy_norm = cv::xfeatures2d::DAISY::NormalizationType::NRM_NONE;
#else
  int daisy_norm = cv::xfeatures2d::DAISY::NRM_NONE;
#endif

  QString norm = DaisyProperties::norm();
  if (norm.compare("NRM_NONE") == 0 ) {
    daisy_norm = cv::xfeatures2d::DAISY::NRM_NONE;
  } else if (norm.compare("NRM_PARTIAL") == 0){
    daisy_norm = cv::xfeatures2d::DAISY::NRM_PARTIAL;
  } else if (norm.compare("NRM_FULL") == 0){
    daisy_norm = cv::xfeatures2d::DAISY::NRM_FULL;
  } else if (norm.compare("NRM_SIFT") == 0){
    daisy_norm = cv::xfeatures2d::DAISY::NRM_SIFT;
  }
  mDAISY = cv::xfeatures2d::DAISY::create(static_cast<float>(DaisyProperties::radius()),
                                          DaisyProperties::qRadius(),
                                          DaisyProperties::qTheta(),
                                          DaisyProperties::qHist(),
                                          daisy_norm, cv::noArray(),
                                          DaisyProperties::interpolation(),
                                          DaisyProperties::useOrientation());
}

bool DaisyDescriptor::extract(const cv::Mat &img,
                              std::vector<cv::KeyPoint> &keyPoints,
                              cv::Mat &descriptors)
{

  try {
      mDAISY->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("DAISY Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void DaisyDescriptor::setRadius(double radius)
{
  DaisyProperties::setRadius(radius);
  update();
}

void DaisyDescriptor::setQRadius(int qRadius)
{
  DaisyProperties::setQRadius(qRadius);
  update();
}

void DaisyDescriptor::setQTheta(int qTheta)
{
  DaisyProperties::setQTheta(qTheta);
  update();
}

void DaisyDescriptor::setQHist(int qHist)
{
  DaisyProperties::setQHist(qHist);
  update();
}

void DaisyDescriptor::setNorm(const QString &norm)
{
  DaisyProperties::setNorm(norm);
  update();
}

void DaisyDescriptor::setInterpolation(bool interpolation)
{
  DaisyProperties::setInterpolation(interpolation);
  update();
}

void DaisyDescriptor::setUseOrientation(bool useOrientation)
{
  DaisyProperties::setUseOrientation(useOrientation);
  update();
}

void DaisyDescriptor::reset()
{
  DaisyProperties::reset();
  update();
}

/*----------------------------------------------------------------*/

} // namespace photomatch
