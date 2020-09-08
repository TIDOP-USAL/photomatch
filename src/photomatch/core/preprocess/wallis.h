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


#ifndef PHOTOMATCH_WALLIS_PREPROCESS_H
#define PHOTOMATCH_WALLIS_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT WallisProperties
  : public Wallis
{

public:

  WallisProperties();
  ~WallisProperties() override;

// IWallis interface

public:

  double contrast() const override;
  void setContrast(double contrast) override;
  double brightness() const override;
  void setBrightness(double brightness) override;
  int imposedAverage() const override;
  void setImposedAverage(int imposedAverage) override;
  int imposedLocalStdDev() const override;
  void setImposedLocalStdDev(int imposedLocalStdDev) override;
  int kernelSize() const override;
  void setKernelSize(int kernelSize) override;

// Preprocess interface

public:

  void reset() override;
  QString name() const final;

private:

  double mContrast;
  double mBrightness;
  int mImposedAverage;
  int mImposedLocalStdDev;
  int mKernelSize;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT WallisPreprocess
  : public WallisProperties,
    public ImageProcess
{

public:

  WallisPreprocess();
  WallisPreprocess(double contrast,
                   double brightness,
                   int imposedAverage,
                   int imposedLocalStdDev,
                   int kernelSize);
  ~WallisPreprocess() override;

private:

  cv::Mat convertToGray32F(const cv::Mat &imageGray);

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &imgIn) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_WALLIS_PREPROCESS_H
