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
  ~HogProperties() override;

// IHog interface

public:

  virtual QSize winSize() const override;
  virtual QSize blockSize() const override;
  virtual QSize blockStride() const override;
  virtual QSize cellSize() const override;
  virtual int nbins() const override;
  virtual int derivAperture() const override;
  virtual void setWinSize(const QSize &winSize) override;
  virtual void setBlockSize(const QSize &blockSize) override;
  virtual void setBlockStride(const QSize &blockStride) override;
  virtual void setCellSize(const QSize &cellSize) override;
  virtual void setNbins(int nbins) override;
  virtual void setDerivAperture(int derivAperture) override;

// Feature interface

public:

  virtual void reset() override;
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

  ~HogDescriptor() override;

private:

  void update();
  void normalizepatch(const cv::Mat &gray, const cv::KeyPoint &keypoint, cv::Mat &output);

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// IHog interface

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
