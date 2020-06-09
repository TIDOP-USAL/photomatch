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


#ifndef PHOTOMATCH_HOG_DESCRIPTOR_H
#define PHOTOMATCH_HOG_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include <memory>

#include <QString>

#include <opencv2/objdetect.hpp>

#include "photomatch/core/features/features.h"

namespace photomatch
{


class PHOTOMATCH_EXPORT HogProperties
  : public Hog
{
public:

  HogProperties();
  HogProperties(const HogProperties &hogProperties);
  ~HogProperties() override = default;

// Hog interface

public:

  QSize winSize() const override;
  QSize blockSize() const override;
  QSize blockStride() const override;
  QSize cellSize() const override;
  int nbins() const override;
  int derivAperture() const override;
  void setWinSize(const QSize &winSize) override;
  void setBlockSize(const QSize &blockSize) override;
  void setBlockStride(const QSize &blockStride) override;
  void setCellSize(const QSize &cellSize) override;
  void setNbins(int nbins) override;
  void setDerivAperture(int derivAperture) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  QSize mWinSize;
  QSize mBlockSize;
  QSize mBlockStride;
  QSize mCellSize;
  int mNbins;
  int mDerivAperture;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT HogDescriptor
    : public HogProperties,
      public DescriptorExtractor
{

public:

  HogDescriptor();
  HogDescriptor(const HogDescriptor &hogDescriptor);
  HogDescriptor(QSize winSize,
                QSize blockSize,
                QSize blockStride,
                QSize cellSize,
                int nbins,
                int derivAperture);
  ~HogDescriptor() override = default;

private:

  void update();
  void normalizepatch(const cv::Mat &gray, const cv::KeyPoint &keypoint, cv::Mat &output);

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// Hog interface

public:

  void setWinSize(const QSize &winSize) override;
  void setBlockSize(const QSize &blockSize) override;
  void setBlockStride(const QSize &blockStride) override;
  void setCellSize(const QSize &cellSize) override;
  void setNbins(int nbins) override;
  void setDerivAperture(int derivAperture) override;

// Feature interface

public:

  void reset() override;

protected:

  std::shared_ptr<cv::HOGDescriptor> mHOG;
};


} // namespace photomatch

#endif // PHOTOMATCH_HOG_DESCRIPTOR_H
