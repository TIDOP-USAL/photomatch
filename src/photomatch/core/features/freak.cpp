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


#include "freak.h"

#include <tidop/core/messages.h>


namespace photomatch
{


FreakProperties::FreakProperties()
  : mOrientationNormalized(true),
    mScaleNormalized(true),
    mPatternScale(22.),
    mOctaves(4)
{
}

FreakProperties::FreakProperties(const FreakProperties &freakProperties)
  : Freak(freakProperties),
    mOrientationNormalized(freakProperties.mOrientationNormalized),
    mScaleNormalized(freakProperties.mScaleNormalized),
    mPatternScale(freakProperties.mPatternScale),
    mOctaves(freakProperties.mOctaves)
{
}

bool FreakProperties::orientationNormalized() const
{
  return mOrientationNormalized;
}

bool FreakProperties::scaleNormalized() const
{
  return mScaleNormalized;
}

double FreakProperties::patternScale() const
{
  return mPatternScale;
}

int FreakProperties::octaves() const
{
  return mOctaves;
}

void FreakProperties::setOrientationNormalized(bool orientationNormalized)
{
  mOrientationNormalized = orientationNormalized;
}

void FreakProperties::setScaleNormalized(bool scaleNormalized)
{
  mScaleNormalized = scaleNormalized;
}

void FreakProperties::setPatternScale(double patternScale)
{
  mPatternScale = patternScale;
}

void FreakProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void FreakProperties::reset()
{
  mOrientationNormalized = true;
  mScaleNormalized = true;
  mPatternScale = 22.;
  mOctaves = 4;
}

QString FreakProperties::name() const
{
  return QString("FREAK");
}


/*----------------------------------------------------------------*/


FreakDescriptor::FreakDescriptor()
{
  update();
}

FreakDescriptor::FreakDescriptor(const FreakDescriptor &freakDescriptor)
  : FreakProperties(freakDescriptor),
    DescriptorExtractor(freakDescriptor)
{
  update();
}


FreakDescriptor::FreakDescriptor(bool orientationNormalized,
                                 bool scaleNormalized,
                                 double patternScale,
                                 int octaves)
{
  FreakProperties::setOrientationNormalized(orientationNormalized);
  FreakProperties::setScaleNormalized(scaleNormalized);
  FreakProperties::setPatternScale(patternScale);
  FreakProperties::setOctaves(octaves);
  update();
}

void FreakDescriptor::update()
{
  mFREAK = cv::xfeatures2d::FREAK::create(FreakProperties::orientationNormalized(),
                                          FreakProperties::scaleNormalized(),
                                          static_cast<float>(FreakProperties::patternScale()),
                                          FreakProperties::octaves());
}

bool FreakDescriptor::extract(const cv::Mat &img,
                              std::vector<cv::KeyPoint> &keyPoints,
                              cv::Mat &descriptors)
{

  try {
    mFREAK->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("FREAK Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void FreakDescriptor::setOrientationNormalized(bool orientationNormalized)
{
  FreakProperties::setOrientationNormalized(orientationNormalized);
  update();
}

void FreakDescriptor::setScaleNormalized(bool scaleNormalized)
{
  FreakProperties::setScaleNormalized(scaleNormalized);
  update();
}

void FreakDescriptor::setPatternScale(double patternScale)
{
  FreakProperties::setPatternScale(patternScale);
  update();
}

void FreakDescriptor::setOctaves(int octaves)
{
  FreakProperties::setOctaves(octaves);
  update();
}

void FreakDescriptor::reset()
{
  FreakProperties::reset();
  update();
}


} // namespace photomatch
