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


#ifndef PHOTOMATCH_DHE_PREPROCESS_H
#define PHOTOMATCH_DHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT DheProperties
  : public Dhe
{

public:

  DheProperties();
  DheProperties(const DheProperties &dheProperties);
  ~DheProperties() override = default;

// IDhe interface

public:

  virtual int x() const override;
  virtual void setX(int x) override;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  int mX;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT DhePreprocess
  : public DheProperties,
    public ImageProcess
{

public:

  DhePreprocess();
  DhePreprocess(const DhePreprocess &dhePreprocess);
  DhePreprocess(int x);
  ~DhePreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_DHE_PREPROCESS_H
