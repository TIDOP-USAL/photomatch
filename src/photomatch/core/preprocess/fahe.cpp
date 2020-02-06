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


#include "fahe.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


FaheProperties::FaheProperties()
  : Fahe(),
    mBlockSize(QSize(11, 11))
{
}

FaheProperties::FaheProperties(const FaheProperties &faheProperties)
  : Fahe(),
    mBlockSize(faheProperties.mBlockSize)
{
}

QSize FaheProperties::blockSize() const
{
  return mBlockSize;
}

void FaheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void FaheProperties::reset()
{
  mBlockSize = QSize(11, 11);
}

QString FaheProperties::name() const
{
  return QString("FAHE");
}


/*----------------------------------------------------------------*/


FahePreprocess::FahePreprocess()
  : FaheProperties(),
    ImageProcess()
{
}

FahePreprocess::FahePreprocess(const FahePreprocess &fahePreprocess)
  : FaheProperties(fahePreprocess),
    ImageProcess()
{
}

FahePreprocess::FahePreprocess(const QSize &blockSize)
  : FaheProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

FahePreprocess::~FahePreprocess()
{

}

bool FahePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{
  try {

    pixkit::enhancement::local::FAHE2006(convertToGray(imgIn), imgOut,
                                         qSizeToCvSize(FaheProperties::blockSize()));

  } catch (cv::Exception &e) {
    msgError("FAHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







