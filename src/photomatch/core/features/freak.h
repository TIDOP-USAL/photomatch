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


#ifndef PHOTOMATCH_FREAK_DESCRIPTOR_H
#define PHOTOMATCH_FREAK_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT FreakProperties
  : public Freak
{

public:

  FreakProperties();
  FreakProperties(const FreakProperties &freakProperties);
  ~FreakProperties() override;

// IFreak interface

public:

  virtual bool orientationNormalized() const override;
  virtual bool scaleNormalized() const override;
  virtual double patternScale() const override;
  virtual int octaves() const override;
  virtual void setOrientationNormalized(bool orientationNormalized) override;
  virtual void setScaleNormalized(bool scaleNormalized) override;
  virtual void setPatternScale(double patternScale) override;
  virtual void setOctaves(int octaves) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  bool mOrientationNormalized;
  bool mScaleNormalized;
  double mPatternScale;
  int mOctaves;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT FreakDescriptor
    : public FreakProperties,
      public DescriptorExtractor
{

public:

  FreakDescriptor();
  FreakDescriptor(const FreakDescriptor &freakDescriptor);
  FreakDescriptor(bool orientationNormalized,
                  bool scaleNormalized,
                  double patternScale,
                  int octaves);

  ~FreakDescriptor() override;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// IFreak interface

public:

  void setOrientationNormalized(bool orientationNormalized) override;
  void setScaleNormalized(bool scaleNormalized) override;
  void setPatternScale(double patternScale) override;
  void setOctaves(int octaves) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::FREAK> mFREAK;
};


} // namespace photomatch

#endif // PHOTOMATCH_FREAK_DESCRIPTOR_H
