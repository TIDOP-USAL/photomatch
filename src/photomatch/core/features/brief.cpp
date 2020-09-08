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


#include "brief.h"

#include <tidop/core/messages.h>


namespace photomatch
{


BriefProperties::BriefProperties()
  : mBytes("32"),
    mUseOrientation(false)
{
}

BriefProperties::BriefProperties(const BriefProperties &briefProperties)
  : Brief(briefProperties),
    mBytes(briefProperties.mBytes),
    mUseOrientation(briefProperties.mUseOrientation)
{
}

QString BriefProperties::bytes() const
{
  return mBytes;
}

bool BriefProperties::useOrientation() const
{
  return mUseOrientation;
}

void BriefProperties::setBytes(const QString &bytes)
{
  if (bytes.compare("16") == 0 ||
      bytes.compare("32") == 0 ||
      bytes.compare("64") == 0) {
    mBytes = bytes;
  }
}

void BriefProperties::setUseOrientation(bool useOrientation)
{
  mUseOrientation = useOrientation;
}

void BriefProperties::reset()
{
  mBytes = "32";
  mUseOrientation = false;
}

QString BriefProperties::name() const
{
  return QString("BRIEF");
}


/*----------------------------------------------------------------*/


BriefDescriptor::BriefDescriptor()
{
  update();
}

BriefDescriptor::BriefDescriptor(const BriefDescriptor &briefDescriptor)
  : BriefProperties(briefDescriptor),
    DescriptorExtractor(briefDescriptor)
{
  update();
}

BriefDescriptor::BriefDescriptor(QString bytes, bool useOrientation)
{
  BriefProperties::setBytes(bytes);
  BriefProperties::setUseOrientation(useOrientation);
  update();
}

void BriefDescriptor::update()
{
  mBrief = cv::xfeatures2d::BriefDescriptorExtractor::create(BriefProperties::bytes().toInt(),
                                                             BriefProperties::useOrientation());
}

cv::Mat BriefDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mBrief->compute(img, keyPoints, descriptors);
  return descriptors;
}

void BriefDescriptor::setBytes(const QString &bytes)
{
  BriefProperties::setBytes(bytes);
  update();
}

void BriefDescriptor::setUseOrientation(bool useOrientation)
{
  BriefProperties::setUseOrientation(useOrientation);
  update();
}

void BriefDescriptor::reset()
{
  BriefProperties::reset();
  update();
}


} // namespace photomatch
