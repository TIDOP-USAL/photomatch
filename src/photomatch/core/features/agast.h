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


/*!
 * \brief AGAST detector properties class
 */
class PHOTOMATCH_EXPORT AgastProperties
  : public Agast
{

public:

  AgastProperties();
  AgastProperties(const AgastProperties &agast);
  ~AgastProperties() override;

// IAgast interface

public:

  virtual int threshold() const override;
  virtual bool nonmaxSuppression() const override;
  virtual QString detectorType() const override;
  virtual void setThreshold(int threshold) override;
  virtual void setNonmaxSuppression(bool nonmaxSuppression) override;
  virtual void setDetectorType(const QString &detectorType) override;

// Feature interface

public:

  virtual void reset() override;
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
  AgastDetector(int threshold, bool nonmaxSuppression, QString detectorType);
  ~AgastDetector() override;

private:

#if CV_VERSION_MAJOR >= 4
  cv::AgastFeatureDetector::DetectorType convertDetectorType(const QString &detectorType);
#else
  int convertDetectorType(const QString &detectorType);
#endif

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// IAgast interface

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
