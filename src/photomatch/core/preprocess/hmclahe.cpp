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


#include "hmclahe.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


HmclaheProperties::HmclaheProperties()
  : Hmclahe(),
    mBlockSize(17,17),
    mL(0.03),
    mPhi(0.5)
{
}

HmclaheProperties::~HmclaheProperties()
{}

QSize HmclaheProperties::blockSize() const
{
  return mBlockSize;
}

void HmclaheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double HmclaheProperties::l() const
{
  return mL;
}

void HmclaheProperties::setL(double l)
{
  mL = l;
}

double HmclaheProperties::phi() const
{
  return mPhi;
}

void HmclaheProperties::setPhi(double phi)
{
  mPhi = phi;
}

void HmclaheProperties::reset()
{
  mBlockSize = QSize(17, 17);
  mL = 0.03;
  mPhi = 0.5;
}

QString HmclaheProperties::name() const
{
  return QString("HMCLAHE");
}


/*----------------------------------------------------------------*/


HmclahePreprocess::HmclahePreprocess()
  : HmclaheProperties(),
    ImageProcess()
{
}

HmclahePreprocess::HmclahePreprocess(const QSize &blockSize, double l, double phi)
  : HmclaheProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
  this->setL(l);
  this->setPhi(phi);
}

HmclahePreprocess::~HmclahePreprocess()
{

}

bool HmclahePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    pixkit::enhancement::local::Sundarami2011(convertToGray(imgIn), imgOut,
                                              qSizeToCvSize(HmclaheProperties::blockSize()),
                                              static_cast<float>(HmclaheProperties::l()),
                                              static_cast<float>(HmclaheProperties::phi()));

  } catch (cv::Exception &e) {
    msgError("HMCLAHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







