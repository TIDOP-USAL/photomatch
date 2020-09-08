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


#ifndef PHOTOMATCH_GFTT_DETECTOR_H
#define PHOTOMATCH_GFTT_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT GfttProperties
  : public Gftt
{
public:

  GfttProperties();
  GfttProperties(const GfttProperties &gfttProperties);
  ~GfttProperties() override = default;

// Gftt interface

public:

  int maxFeatures() const override;
  double qualityLevel() const override;
  double minDistance() const override;
  int blockSize() const override;
  bool harrisDetector() const override;
  double k() const override;
  void setMaxFeatures(int maxFeatures) override;
  void setQualityLevel(double qlevel) override;
  void setMinDistance(double minDistance) override;
  void setBlockSize(int blockSize) override;
  void setHarrisDetector(bool value) override;
  void setK(double k) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mMaxFeatures;
  double mQualityLevel;
  double mMinDistance;
  int mBlockSize;
  bool mHarrisDetector;
  double mK;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT GfttDetector
  : public GfttProperties,
    public KeypointDetector
{

public:

  GfttDetector();
  GfttDetector(const GfttDetector &gfttDetector);
  GfttDetector(int maxFeatures,
               double qualityLevel,
               double minDistance,
               int blockSize,
               bool harrisDetector,
               double k);
  ~GfttDetector() override = default;

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img,
                                   const cv::Mat &mask = cv::Mat()) override;

// Gftt interface

public:

  void setMaxFeatures(int maxFeatures) override;
  void setQualityLevel(double qlevel) override;
  void setMinDistance(double minDistance) override;
  void setBlockSize(int blockSize) override;
  void setHarrisDetector(bool value) override;
  void setK(double k) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::GFTTDetector> mGFTT;

};


} // namespace photomatch

#endif // PHOTOMATCH_GFTT_DETECTOR_H
