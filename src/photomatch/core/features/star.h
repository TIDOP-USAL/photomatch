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


#ifndef PHOTOMATCH_STAR_DETECTOR_H
#define PHOTOMATCH_STAR_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT StarProperties
  : public Star
{
public:

  StarProperties();
  StarProperties(const StarProperties &starProperties);
  ~StarProperties() override = default;

// Star interface

public:

  int maxSize() const override;
  int responseThreshold() const override;
  int lineThresholdProjected() const override;
  int lineThresholdBinarized() const override;
  int suppressNonmaxSize() const override;
  void setMaxSize(int maxSize) override;
  void setResponseThreshold(int responseThreshold) override;
  void setLineThresholdProjected(int lineThresholdProjected) override;
  void setLineThresholdBinarized(int lineThresholdBinarized) override;
  void setSuppressNonmaxSize(int suppressNonmaxSize) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mMaxSize;
  int mResponseThreshold;
  int mLineThresholdProjected;
  int mLineThresholdBinarized;
  int mSuppressNonmaxSize;
};



/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT StarDetector
  : public StarProperties,
    public KeypointDetector
{

public:

  StarDetector();
  StarDetector(const StarDetector &starDetector);
  StarDetector(int maxSize,
               int responseThreshold,
               int lineThresholdProjected,
               int lineThresholdBinarized,
               int suppressNonmaxSize);
  ~StarDetector() override = default;

private:

  void update();

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// Star interface

public:

  void setMaxSize(int maxSize) override;
  void setResponseThreshold(int responseThreshold) override;
  void setLineThresholdProjected(int lineThresholdProjected) override;
  void setLineThresholdBinarized(int lineThresholdBinarized) override;
  void setSuppressNonmaxSize(int suppressNonmaxSize) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::StarDetector> mSTAR;

};


} // namespace photomatch

#endif // PHOTOMATCH_STAR_DETECTOR_H
