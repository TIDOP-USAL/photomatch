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


#include "brisk.h"

#include <tidop/core/messages.h>


namespace photomatch
{


BriskProperties::BriskProperties()
  : mThreshold(30),
    mOctaves(3),
    mPatternScale(1.0)
{}

BriskProperties::BriskProperties(const BriskProperties &briskProperties)
  : Brisk(briskProperties),
    mThreshold(briskProperties.mThreshold),
    mOctaves(briskProperties.mOctaves),
    mPatternScale(briskProperties.mPatternScale)
{}

int BriskProperties::threshold() const
{
  return mThreshold;
}

int BriskProperties::octaves() const
{
  return mOctaves;
}

double BriskProperties::patternScale() const
{
  return mPatternScale;
}

void BriskProperties::setThreshold(int threshold)
{
  mThreshold = threshold;
}

void BriskProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void BriskProperties::setPatternScale(double patternScale)
{
  mPatternScale = patternScale;
}

void BriskProperties::reset()
{
  mThreshold = 30;
  mOctaves = 3;
  mPatternScale = 1.0;
}

QString BriskProperties::name() const
{
  return QString("BRISK");
}


/*----------------------------------------------------------------*/


BriskDetectorDescriptor::BriskDetectorDescriptor()
{
  update();
}

BriskDetectorDescriptor::BriskDetectorDescriptor(const BriskDetectorDescriptor &briskDetectorDescriptor)
  : BriskProperties(briskDetectorDescriptor),
    KeypointDetector(briskDetectorDescriptor),
    DescriptorExtractor(briskDetectorDescriptor)
{
  update();
}


BriskDetectorDescriptor::BriskDetectorDescriptor(int threshold,
                                                 int octaves,
                                                 double patternScale)
{
  BriskProperties::setThreshold(threshold);
  BriskProperties::setOctaves(octaves);
  BriskProperties::setPatternScale(patternScale);
  update();
}

void BriskDetectorDescriptor::update()
{
  mBrisk = cv::BRISK::create(BriskProperties::threshold(),
                             BriskProperties::octaves(),
                             static_cast<float>(BriskProperties::patternScale()));
}

bool BriskDetectorDescriptor::detect(const cv::Mat &img,
                                     std::vector<cv::KeyPoint> &keyPoints,
                                     cv::InputArray &mask)
{

  try {
    mBrisk->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("BRISK Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool BriskDetectorDescriptor::extract(const cv::Mat &img,
                                      std::vector<cv::KeyPoint> &keyPoints,
                                      cv::Mat &descriptors)
{
  try {
    mBrisk->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("BRISK Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void BriskDetectorDescriptor::setThreshold(int threshold)
{
  BriskProperties::setThreshold(threshold);
  update();
}

void BriskDetectorDescriptor::setOctaves(int octaves)
{
  BriskProperties::setOctaves(octaves);
  update();
}

void BriskDetectorDescriptor::setPatternScale(double patternScale)
{
  BriskProperties::setPatternScale(patternScale);
  update();
}

void BriskDetectorDescriptor::reset()
{
  BriskProperties::reset();
  update();
}


} // namespace photomatch
