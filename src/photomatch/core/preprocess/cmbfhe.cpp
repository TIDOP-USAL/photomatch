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


#include "cmbfhe.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


CmbfheProperties::CmbfheProperties()
  : Cmbfhe(),
    mBlockSize(11,11)
{}

CmbfheProperties::CmbfheProperties(const CmbfheProperties &cmbfheProperties)
  : Cmbfhe(),
    mBlockSize(cmbfheProperties.blockSize())
{}

QSize CmbfheProperties::blockSize() const
{
  return mBlockSize;
}

void CmbfheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void CmbfheProperties::reset()
{
  mBlockSize = QSize(11,11);
}

QString CmbfheProperties::name() const
{
  return QString("CMBFHE");
}


/*----------------------------------------------------------------*/


CmbfhePreprocess::CmbfhePreprocess()
  : CmbfheProperties(),
    ImageProcess()
{
}

CmbfhePreprocess::CmbfhePreprocess(const CmbfhePreprocess &cmbfhePreprocess)
  : CmbfheProperties(cmbfhePreprocess),
    ImageProcess()
{
}

CmbfhePreprocess::CmbfhePreprocess(const QSize &blockSize)
  : CmbfheProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

CmbfhePreprocess::~CmbfhePreprocess()
{

}

cv::Mat CmbfhePreprocess::process(const cv::Mat &imgIn)
{
  cv::Mat imgOut;

  pixkit::enhancement::local::LambertiMontrucchioSanna2006(convertToGray(imgIn), imgOut,
                                                           qSizeToCvSize(CmbfheProperties::blockSize()),
                                                           cv::Size(44,44));

  return imgOut;
}

} // namespace photomatch







