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


#ifndef PHOTOMATCH_MSRCP_PREPROCESS_H
#define PHOTOMATCH_MSRCP_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT MsrcpProperties
  : public Msrcp
{

public:

  MsrcpProperties();
  ~MsrcpProperties() override;

// IMsrcp interface

public:

  double smallScale() const override;
  void setSmallScale(double smallScale) override;
  double midScale() const override;
  void setMidScale(double midScale) override;
  double largeScale() const override;
  void setLargeScale(double largeScale) override;

// Preprocess interface

public:

  void reset() override;
  QString name() const final;

private:

  double mSmallScale;
  double mMidScale;
  double mLargeScale;
};



/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT MsrcpPreprocess
  : public MsrcpProperties,
    public ImageProcess
{

public:

  MsrcpPreprocess();
  MsrcpPreprocess(double smallScale, 
                  double midScale, 
                  double largeScale);
  ~MsrcpPreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &imgIn) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_MSRCP_PREPROCESS_H
