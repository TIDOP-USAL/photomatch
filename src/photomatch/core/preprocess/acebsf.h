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


#ifndef PHOTOMATCH_ACEBSF_PREPROCESS_H
#define PHOTOMATCH_ACEBSF_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT AcebsfProperties
  : public Acebsf
{

public:

  AcebsfProperties();
  AcebsfProperties(const AcebsfProperties &acebsfProperties);
  AcebsfProperties(AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT;
  ~AcebsfProperties() override {}

  AcebsfProperties &operator = (const AcebsfProperties& acebsfProperties);
  AcebsfProperties &operator = (AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT;

// IAcebs interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;
  double l() const override;
  void setL(double l) override;
  double k1() const override;
  void setK1(double k1) override;
  double k2() const override;
  void setK2(double k2) override;

// Preprocess interface

public:

  void reset() override;
  QString name() const final;

private:

  QSize mBlockSize;
  double mL;
  double mK1;
  double mK2;

};



class PHOTOMATCH_EXPORT AcebsfPreprocess
  : public AcebsfProperties,
    public ImageProcess
{

public:

  AcebsfPreprocess();
  AcebsfPreprocess(const AcebsfPreprocess &acebsfPreprocess);
  AcebsfPreprocess(AcebsfPreprocess &&acebsfPreprocess) PHOTOMATCH_NOEXCEPT;
  AcebsfPreprocess(const QSize &blockSize,
                   double l,
                   double k1,
                   double k2);
  ~AcebsfPreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &imgIn) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_ACEBSF_PREPROCESS_H
