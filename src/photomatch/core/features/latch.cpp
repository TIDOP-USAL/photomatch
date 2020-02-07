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


#include "latch.h"

#include <tidop/core/messages.h>


namespace photomatch
{

LatchProperties::LatchProperties()
  : Latch(),
    mBytes("32"),
    mRotationInvariance(true),
    mHalfSsdSize(3)
{
}

LatchProperties::LatchProperties(const LatchProperties &latchProperties)
  : Latch(),
    mBytes(latchProperties.mBytes),
    mRotationInvariance(latchProperties.mRotationInvariance),
    mHalfSsdSize(latchProperties.mHalfSsdSize)
{
}

LatchProperties::~LatchProperties()
{

}

QString LatchProperties::bytes() const
{
  return mBytes;
}

bool LatchProperties::rotationInvariance() const
{
  return mRotationInvariance;
}

int LatchProperties::halfSsdSize() const
{
  return mHalfSsdSize;
}

void LatchProperties::setBytes(const QString &bytes)
{
  if (bytes.compare("1") == 0 ||
      bytes.compare("2") == 0 ||
      bytes.compare("4") == 0 ||
      bytes.compare("8") == 0 ||
      bytes.compare("16") == 0 ||
      bytes.compare("32") == 0 ||
      bytes.compare("64") == 0) {
    mBytes = bytes;
  }
}

void LatchProperties::setRotationInvariance(bool rotationInvariance)
{
  mRotationInvariance = rotationInvariance;
}

void LatchProperties::setHalfSsdSize(int halfSsdSize)
{
  mHalfSsdSize = halfSsdSize;
}

void LatchProperties::reset()
{
  mBytes = "32";
  mRotationInvariance = true;
  mHalfSsdSize = 3;
}

QString LatchProperties::name() const
{
  return QString("LATCH");
}


/*----------------------------------------------------------------*/


LatchDescriptor::LatchDescriptor()
  : LatchProperties(),
    DescriptorExtractor()
{
  update();
}

LatchDescriptor::LatchDescriptor(const LatchDescriptor &latchDescriptor)
  : LatchProperties(latchDescriptor),
    DescriptorExtractor()
{
  update();
}

LatchDescriptor::LatchDescriptor(QString bytes,
                                 bool rotationInvariance,
                                 int halfSsdSize)
  : LatchProperties(),
    DescriptorExtractor()
{
  LatchProperties::setBytes(bytes);
  LatchProperties::setRotationInvariance(rotationInvariance);
  LatchProperties::setHalfSsdSize(halfSsdSize);
  update();
}

LatchDescriptor::~LatchDescriptor()
{

}

void LatchDescriptor::update()
{
  mLATCH = cv::xfeatures2d::LATCH::create(LatchProperties::bytes().toInt(),
                                          LatchProperties::rotationInvariance(),
                                          LatchProperties::halfSsdSize());
}

bool LatchDescriptor::extract(const cv::Mat &img,
                              std::vector<cv::KeyPoint> &keyPoints,
                              cv::Mat &descriptors)
{

  try {
    mLATCH->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("LATCH Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void LatchDescriptor::setBytes(const QString &bytes)
{
  LatchProperties::setBytes(bytes);
  update();
}

void LatchDescriptor::setRotationInvariance(bool rotationInvariance)
{
  LatchProperties::setRotationInvariance(rotationInvariance);
  update();
}

void LatchDescriptor::setHalfSsdSize(int halfSsdSize)
{
  LatchProperties::setHalfSsdSize(halfSsdSize);
  update();
}

void LatchDescriptor::reset()
{
  LatchProperties::reset();
  update();
}



} // namespace photomatch
