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


#include "rswhe.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


RswheProperties::RswheProperties()
  : Rswhe(),
    mHistogramCut(HistogramCut::by_mean),
    mHistogramDivisions(2)
{
}

RswheProperties::~RswheProperties()
{

}

int RswheProperties::histogramDivisions() const
{
  return mHistogramDivisions;
}

void RswheProperties::setHistogramDivisions(int histogramDivisions)
{
  mHistogramDivisions = histogramDivisions;
}

Rswhe::HistogramCut RswheProperties::histogramCut() const
{
  return mHistogramCut;
}

void RswheProperties::setHistogramCut(photomatch::Rswhe::HistogramCut histogramCut)
{
  mHistogramCut = histogramCut;
}

void RswheProperties::reset()
{
  mHistogramDivisions = 2;
  mHistogramCut = HistogramCut::by_mean;
}

QString RswheProperties::name() const
{
  return QString("RSWHE");
}


/*----------------------------------------------------------------*/


RswhePreprocess::RswhePreprocess()
  : RswheProperties(),
    ImageProcess()
{
}

RswhePreprocess::RswhePreprocess(int histogramDivisions, HistogramCut histogramCut)
  : RswheProperties(),
    ImageProcess()
{
  this->setHistogramDivisions(histogramDivisions);
  this->setHistogramCut(histogramCut);
}

RswhePreprocess::~RswhePreprocess()
{

}

cv::Mat RswhePreprocess::process(const cv::Mat &imgIn)
{
  cv::Mat imgOut;

  int histogram_cut;
  if (RswheProperties::histogramCut() == HistogramCut::by_mean)
    histogram_cut = 1;
  else {
    histogram_cut = 2;
  }

  pixkit::enhancement::global::MaryKim2008(convertToGray(imgIn), imgOut,
                                           histogram_cut,
                                           RswheProperties::histogramDivisions());

  return imgOut;
}


} // namespace photomatch







