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


#include "noshp.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


NoshpProperties::NoshpProperties()
  : Noshp(),
    mBlockSize(127, 127)
{
}

NoshpProperties::~NoshpProperties()
{

}

QSize NoshpProperties::blockSize() const
{
  return mBlockSize;
}

void NoshpProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void NoshpProperties::reset()
{
  mBlockSize = QSize(127, 127);
}

QString NoshpProperties::name() const
{
  return QString("NOSHP");
}


/*----------------------------------------------------------------*/


NoshpPreprocess::NoshpPreprocess()
  : NoshpProperties(),
    ImageProcess()
{
}

NoshpPreprocess::NoshpPreprocess(const QSize &blockSize)
  : NoshpProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

NoshpPreprocess::~NoshpPreprocess()
{

}

bool NoshpPreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    pixkit::enhancement::local::LiuJinChenLiuLi2011(convertToGray(imgIn), 
                                                    imgOut,
                                                    qSizeToCvSize(NoshpProperties::blockSize()));

  } catch (cv::Exception &e) {
    msgError("NOSHP Image preprocess error: %s", e.what());
    return true;
  }


  return false;
}


} // namespace photomatch







