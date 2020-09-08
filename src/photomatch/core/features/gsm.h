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

#ifndef PHOTOMATCH_GSM_H
#define PHOTOMATCH_GSM_H

#include "photomatch/photomatch_global.h"
#include "photomatch/core/features/matcher.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT GmsProperties
  : public Gms
{

public:

  GmsProperties();
  ~GmsProperties() override = default;


// MatchingStrategy interface

public:

  void reset() override;
  QString name() const override;

// IGms interface

public:

  bool rotation() const override;
  void setRotation(bool rotation) override;
  bool scale() const override;
  void setScale(bool scale) override;
  double threshold() const override;
  void setThreshold(double threshold) override;

protected:

  bool mRotation;
  bool mScale;
  double mThreshold;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT GsmImp
  : public GmsProperties,
    public MatchingAlgorithm
{

public:

  explicit GsmImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher);
  GsmImp(const std::shared_ptr<DescriptorMatcher> &descriptorMatcher,
         bool rotation,
         bool scale,
         double threshold);
  ~GsmImp() override = default;

// MatchingAlgorithm interface

public:

  bool compute(const cv::Mat &queryDescriptor,
               const cv::Mat &trainDescriptor,
               const std::vector<cv::KeyPoint> &keypoints1,
               const std::vector<cv::KeyPoint> &keypoints2,
               std::vector<cv::DMatch> *goodMatches,
               std::vector<cv::DMatch> *wrongMatches = nullptr,
               const QSize &queryImageSize = QSize(),
               const QSize &trainImageSize = QSize()) override;

protected:

  std::shared_ptr<DescriptorMatcher> mDescriptorMatcher;

};

} // namespace photomatch

#endif // PHOTOMATCH_GSM_H
