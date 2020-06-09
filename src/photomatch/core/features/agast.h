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


#ifndef PHOTOMATCH_AGAST_DETECTOR_H
#define PHOTOMATCH_AGAST_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT AgastProperties
  : public Agast
{

public:

  AgastProperties();
  AgastProperties(const AgastProperties &agast);
  AgastProperties(AgastProperties &&agast) noexcept;
  ~AgastProperties() override = default;

  AgastProperties &operator =(const AgastProperties &agast);
  AgastProperties &operator =(AgastProperties &&agast) noexcept;

// Agast interface

public:

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;
  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(const QString &detectorType) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mThreshold;
  bool mNonmaxSuppression;
  QString mDetectorType;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT AgastDetector
  : public AgastProperties,
    public KeypointDetector
{

public:

  AgastDetector();
  AgastDetector(const AgastDetector &agastDetector);
  AgastDetector(AgastDetector &&agastDetector) noexcept;
  AgastDetector(int threshold,
                bool nonmaxSuppression,
                const QString &detectorType);
  ~AgastDetector() override = default;
  AgastDetector &operator =(const AgastDetector &agastDetector);
  AgastDetector &operator =(AgastDetector &&agastDetector) noexcept;

private:

#if CV_VERSION_MAJOR >= 4
  cv::AgastFeatureDetector::DetectorType convertDetectorType(const QString &detectorType);
#else
  int convertDetectorType(const QString &detectorType);
#endif

  void initAgastFromProperties();

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// Agast interface

public:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(const QString &detectorType) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::AgastFeatureDetector> mAgast;

};


} // namespace photomatch

#endif // PHOTOMATCH_AGAST_DETECTOR_H
