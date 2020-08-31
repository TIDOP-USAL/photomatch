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


#include "pohe.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


PoheProperties::PoheProperties()
  : Pohe(),
    mBlockSize(127, 127)
{
}

PoheProperties::~PoheProperties()
{

}

QSize PoheProperties::blockSize() const
{
  return mBlockSize;
}

void PoheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void PoheProperties::reset()
{
  mBlockSize = QSize(127, 127);
}

QString PoheProperties::name() const
{
  return QString("POHE");
}


/*----------------------------------------------------------------*/


PohePreprocess::PohePreprocess()
  : PoheProperties(),
    ImageProcess()
{
}

PohePreprocess::PohePreprocess(const QSize &blockSize)
  : PoheProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

PohePreprocess::~PohePreprocess()
{

}

bool PohePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{
  try {

    cv::Mat tmp;
    if (imgIn.channels() == 1)
      cv::cvtColor(imgIn, tmp, cv::COLOR_GRAY2BGR);
    else
      imgIn.copyTo(tmp);

    pixkit::enhancement::local::POHE2013(tmp, 
                                         imgOut, 
                                         qSizeToCvSize(PoheProperties::blockSize()));
    tmp.release();

    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgOut, imgOut, color_boost);
      color_boost.release();
    } else {
      cv::cvtColor(imgOut, imgOut, cv::COLOR_BGR2GRAY);
    }

  } catch (cv::Exception &e) {
    msgError("POHE Image preprocess error: %s", e.what());
    return true;
  }

  return false;
}


} // namespace photomatch

