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


#include "d2net.h"

#include <tidop/core/messages.h>


namespace photomatch
{


D2NetProperties::D2NetProperties()
  : mMultiscale(false)
{
}

D2NetProperties::D2NetProperties(const D2NetProperties &d2NetProperties)
  : D2Net(d2NetProperties),
    mMultiscale(d2NetProperties.mMultiscale)
{
}

bool D2NetProperties::multiscale() const
{
  return mMultiscale;
}

void D2NetProperties::setMultiscale(bool multiscale)
{
  mMultiscale = multiscale;
}

void D2NetProperties::reset()
{
  mMultiscale = false;
}

QString D2NetProperties::name() const
{
  return QString("D2Net");
}



/*----------------------------------------------------------------*/


D2NetDetectorDescriptor::D2NetDetectorDescriptor()
{

}

D2NetDetectorDescriptor::D2NetDetectorDescriptor(const D2NetDetectorDescriptor &d2NetDetectorDescriptor)
  : D2NetProperties(d2NetDetectorDescriptor),
    KeypointDetector(d2NetDetectorDescriptor),
    DescriptorExtractor(d2NetDetectorDescriptor)
{

}

D2NetDetectorDescriptor::D2NetDetectorDescriptor(bool multiscale)
{
  setMultiscale(multiscale);
}

std::vector<cv::KeyPoint> D2NetDetectorDescriptor::detect(const cv::Mat &img, 
                                                          const cv::Mat &mask)
{
  std::vector<cv::KeyPoint> keyPoints;

  return keyPoints;
}

cv::Mat D2NetDetectorDescriptor::extract(const cv::Mat &img, 
                                         std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;

  return descriptors;
}

void D2NetDetectorDescriptor::reset()
{
  D2NetDetectorDescriptor::reset();
}


} // namespace photomatch
