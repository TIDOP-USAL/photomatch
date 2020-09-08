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


#ifndef PHOTOMATCH_RSWHE_PREPROCESS_H
#define PHOTOMATCH_RSWHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT RswheProperties
  : public Rswhe
{

public:

  RswheProperties();
  ~RswheProperties() override;

// IRswhe interface

public:

  int histogramDivisions() const override;
  void setHistogramDivisions(int histogramDivisions) override;
  HistogramCut histogramCut() const override;
  void setHistogramCut(HistogramCut histogramCut) override;

// Preprocess interface

public:

  void reset() override;
  QString name() const final;

private:

  HistogramCut mHistogramCut;
  int mHistogramDivisions;

};



/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT RswhePreprocess
  : public RswheProperties,
    public ImageProcess
{

public:

  RswhePreprocess();
  RswhePreprocess(int histogramDivisions, HistogramCut histogramCut);
  ~RswhePreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &imgIn) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_RSWHE_PREPROCESS_H
