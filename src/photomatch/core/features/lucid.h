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


#ifndef PHOTOMATCH_LUCID_DESCRIPTOR_H
#define PHOTOMATCH_LUCID_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT LucidProperties
  : public Lucid
{
public:

  LucidProperties();
  ~LucidProperties() override = default;

// Lucid interface

public:

  int lucidKernel() const override;
  int blurKernel() const override;
  void setLucidKernel(int lucidKernel) override;
  void setBlurKernel(int blurKernel) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mLucidKernel;
  int mBlurKernel;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT LucidDescriptor
    : public LucidProperties,
      public DescriptorExtractor
{

public:

  LucidDescriptor();
  LucidDescriptor(int lucidKernel, int blurKernel);
  ~LucidDescriptor() override = default;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;


// Lucid interface

public:

  void setLucidKernel(int lucidKernel) override;
  void setBlurKernel(int blurKernel) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::LUCID> mLUCID;
};


} // namespace photomatch

#endif // PHOTOMATCH_LUCID_DESCRIPTOR_H
