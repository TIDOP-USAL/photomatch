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


#ifndef PHOTOMATCH_LATCH_DESCRIPTOR_H
#define PHOTOMATCH_LATCH_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{



class PHOTOMATCH_EXPORT LatchProperties
  : public Latch
{

public:

  LatchProperties();
  LatchProperties(const LatchProperties &latchProperties);
  ~LatchProperties() override = default;

// ILatch interface

public:

  QString bytes() const override;
  bool rotationInvariance() const override;
  int halfSsdSize() const override;
  void setBytes(const QString &bytes) override;
  void setRotationInvariance(bool rotationInvariance) override;
  void setHalfSsdSize(int halfSsdSize) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  QString mBytes;
  bool mRotationInvariance;
  int mHalfSsdSize;
};

/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT LatchDescriptor
    : public LatchProperties,
      public DescriptorExtractor
{

public:

  LatchDescriptor();
  LatchDescriptor(const LatchDescriptor &latchDescriptor);
  LatchDescriptor(const QString& bytes,
                  bool rotationInvariance,
                  int halfSsdSize);

  ~LatchDescriptor() override = default;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;


// IBrief interface

public:

  void setBytes(const QString &bytes) override;
  void setRotationInvariance(bool rotationInvariance) override;
  void setHalfSsdSize(int halfSsdSize) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::LATCH> mLATCH;
};



} // namespace photomatch

#endif // PHOTOMATCH_LATCH_DESCRIPTOR_H
