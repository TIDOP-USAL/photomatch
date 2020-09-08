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


#include "lce_bsescs.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


LceBsescsProperties::LceBsescsProperties()
  : LceBsescs(),
    mBlockSize(33, 33)
{}

LceBsescsProperties::~LceBsescsProperties()
{
}

QSize LceBsescsProperties::blockSize() const
{
  return mBlockSize;
}

void LceBsescsProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void LceBsescsProperties::reset()
{
  mBlockSize = QSize(33, 33);
}

QString LceBsescsProperties::name() const
{
  return QString("LCE_BSESCS");
}


/*----------------------------------------------------------------*/


LceBsescsPreprocess::LceBsescsPreprocess()
  : LceBsescsProperties(),
    ImageProcess()
{
}

LceBsescsPreprocess::LceBsescsPreprocess(const QSize &blockSize)
  : LceBsescsProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

LceBsescsPreprocess::~LceBsescsPreprocess()
{

}

cv::Mat LceBsescsPreprocess::process(const cv::Mat &imgIn)
{
  cv::Mat imgOut;

  pixkit::enhancement::local::LCE_BSESCS2014(convertToGray(imgIn), imgOut,
                                             qSizeToCvSize(LceBsescsProperties::blockSize()));

  return imgOut;
}

} // namespace photomatch







