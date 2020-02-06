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


#ifndef PHOTOMATCH_BOOST_DESCRIPTOR_H
#define PHOTOMATCH_BOOST_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

#include <opencv2/xfeatures2d.hpp>

namespace photomatch
{

class BoostProperties
  : public Boost
{

public:

  BoostProperties();
  BoostProperties(const BoostProperties &boostProperties);
  virtual ~BoostProperties() override;

// IBoost interface

public:

  virtual QString descriptorType() const override;
  virtual bool useOrientation() const override;
  virtual double scaleFactor() const override;
  virtual void setDescriptorType(const QString &descriptorType) override;
  virtual void setUseOrientation(bool useOrientation) override;
  virtual void setScaleFactor(double scaleFactor) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const override;

private:

  QString mDescriptorType;
  bool bUseOrientation;
  double mScaleFactor;

};


/*----------------------------------------------------------------*/

class BoostDescriptor
  : public BoostProperties,
    public DescriptorExtractor
{

public:

  BoostDescriptor();
  BoostDescriptor(const BoostDescriptor &boostDescriptor);
  BoostDescriptor(QString descriptorType,
                  bool useOrientation,
                  double scaleFactor);
  ~BoostDescriptor() override;

private:

  void update();

// Feature interface

public:

  void reset() override;

// IBoost interface

public:

  void setDescriptorType(const QString &descriptorType) override;
  void setUseOrientation(bool useOrientation) override;
  void setScaleFactor(double scaleFactor) override;

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints, cv::Mat &descriptors) override;

protected:

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  cv::Ptr<cv::xfeatures2d::BoostDesc> mBoost;
#endif

};



} // namespace photomatch

#endif // PHOTOMATCH_BOOST_DESCRIPTOR_H
