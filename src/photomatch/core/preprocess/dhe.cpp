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


#include "dhe.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


DheProperties::DheProperties()
  : Dhe(),
    mX(1)
{
}

DheProperties::DheProperties(const DheProperties &dheProperties)
  : Dhe(),
    mX(dheProperties.mX)
{
}

int DheProperties::x() const
{
  return mX;
}

void DheProperties::setX(int x)
{
  mX = x;
}

void DheProperties::reset()
{
  mX = 1;
}

QString DheProperties::name() const
{
  return QString("DHE");
}


/*----------------------------------------------------------------*/


DhePreprocess::DhePreprocess()
  : DheProperties(),
    ImageProcess()
{
}

DhePreprocess::DhePreprocess(const DhePreprocess &dhePreprocess)
  : DheProperties(dhePreprocess),
    ImageProcess()
{
}

DhePreprocess::DhePreprocess(int x)
  : DheProperties(),
    ImageProcess()
{
  this->setX(x);
}

DhePreprocess::~DhePreprocess()
{

}

bool DhePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    pixkit::enhancement::global::WadudKabirDewanChae2007(convertToGray(imgIn), imgOut, DheProperties::x());

  } catch (cv::Exception &e) {
    msgError("DHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







