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


#include "decolor.h"

#include "photomatch/core/utils.h"

#include <opencv2/photo.hpp>

namespace photomatch
{

DecolorProperties::DecolorProperties()
{
}

void DecolorProperties::reset()
{
}

QString DecolorProperties::name() const
{
  return QString("Decolorization");
}




/*----------------------------------------------------------------*/


DecolorPreprocess::DecolorPreprocess()
  : DecolorProperties(),
    ImageProcess()
{
}

DecolorPreprocess::~DecolorPreprocess()
{
}

cv::Mat DecolorPreprocess::process(const cv::Mat &imgIn)
{

  cv::Mat imgOut;

  imgOut = convertToGray(imgIn);

  return imgOut;
}


} // namespace photomatch
