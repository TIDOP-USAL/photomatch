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


#ifndef PHOTOMATCH_DAISY_DESCRIPTOR_H
#define PHOTOMATCH_DAISY_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{

class PHOTOMATCH_EXPORT DaisyProperties
  : public Daisy
{
public:

  DaisyProperties();
  DaisyProperties(const DaisyProperties &daisyProperties);
  ~DaisyProperties() override = default;

// Daisy interface

public:

  double radius() const override;
  int qRadius() const override;
  int qTheta() const override;
  int qHist() const override;
  QString norm() const override;
  bool interpolation() const override;
  bool useOrientation() const override;
  void setRadius(double radius) override;
  void setQRadius(int qRadius) override;
  void setQTheta(int qTheta) override;
  void setQHist(int qHist) override;
  void setNorm(const QString &norm) override;
  void setInterpolation(bool interpolation) override;
  void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  double mRadius;
  int mQRadius;
  int mQTheta;
  int mQHist;
  QString mNorm;
  bool mInterpolation;
  bool mUseOrientation;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT DaisyDescriptor
    : public DaisyProperties,
      public DescriptorExtractor
{

public:

  DaisyDescriptor();
  DaisyDescriptor(const DaisyDescriptor &daisyDescriptor);
  DaisyDescriptor(double radius,
                  int qRadius,
                  int qTheta,
                  int qHist,
                  const QString &norm,
                  bool interpolation,
                  bool useOrientation);
  ~DaisyDescriptor() override = default;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;


// Daisy interface

public:

  void setRadius(double radius) override;
  void setQRadius(int qRadius) override;
  void setQTheta(int qTheta) override;
  void setQHist(int qHist) override;
  void setNorm(const QString &norm) override;
  void setInterpolation(bool interpolation) override;
  void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::DAISY> mDAISY;
};


} // namespace photomatch

#endif // PHOTOMATCH_DAISY_DESCRIPTOR_H
