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


#include "agast.h"

#include <tidop/core/messages.h>


namespace photomatch
{


AgastProperties::AgastProperties()
  : mThreshold(10),
    mNonmaxSuppression(true),
    mDetectorType("OAST_9_16")
{
}

AgastProperties::AgastProperties(const AgastProperties &agast)
  : mThreshold(agast.mThreshold),
    mNonmaxSuppression(agast.nonmaxSuppression()),
    mDetectorType(agast.mDetectorType)
{
}

AgastProperties::AgastProperties(AgastProperties &&agast) noexcept
  : mThreshold(std::move(agast.mThreshold)),
    mNonmaxSuppression(std::move(agast.nonmaxSuppression())),
    mDetectorType(std::move(agast.mDetectorType))
{
}

AgastProperties &AgastProperties::operator =(const AgastProperties &agast)
{
  if (this != &agast) {
    this->mThreshold = agast.mThreshold;
    this->mNonmaxSuppression = agast.mNonmaxSuppression;
    this->mDetectorType = agast.mDetectorType;
  }
  return *this;
}

AgastProperties &AgastProperties::operator =(AgastProperties &&agast) noexcept
{
  if (this != &agast) {
    this->mThreshold = std::move(agast.mThreshold);
    this->mNonmaxSuppression = std::move(agast.mNonmaxSuppression);
    this->mDetectorType = std::move(agast.mDetectorType);
  }
  return *this;
}

int AgastProperties::threshold() const
{
  return mThreshold;
}

bool AgastProperties::nonmaxSuppression() const
{
  return mNonmaxSuppression;
}

QString AgastProperties::detectorType() const
{
  return mDetectorType;
}

void AgastProperties::setThreshold(int threshold)
{
  mThreshold = threshold;
}

void AgastProperties::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression = nonmaxSuppression;
}

void AgastProperties::setDetectorType(const QString &detectorType)
{
  if (detectorType.compare("AGAST_5_8") == 0 ||
      detectorType.compare("AGAST_7_12d") == 0 ||
      detectorType.compare("AGAST_7_12s") == 0 ||
      detectorType.compare("OAST_9_16") == 0) {
    mDetectorType = detectorType;
  }
}

void AgastProperties::reset()
{
  mThreshold = 10;
  mNonmaxSuppression = true;
  mDetectorType = "OAST_9_16";
}

QString AgastProperties::name() const
{
  return QString("AGAST");
}


/*----------------------------------------------------------------*/


AgastDetector::AgastDetector()
{
  this->initAgastFromProperties();
}

AgastDetector::AgastDetector(const AgastDetector &agastDetector)
  : AgastProperties(agastDetector)
{
  this->initAgastFromProperties();
}

AgastDetector::AgastDetector(AgastDetector &&agastDetector) noexcept
  : AgastProperties(std::forward<AgastProperties>(agastDetector))
{
  this->initAgastFromProperties();
}

AgastDetector::AgastDetector(int threshold, bool nonmaxSuppression, const QString &detectorType)
  : mAgast(cv::AgastFeatureDetector::create())
{
  setThreshold(threshold);
  setNonmaxSuppression(nonmaxSuppression);
  setDetectorType(detectorType);
}

AgastDetector &AgastDetector::operator =(const AgastDetector &agastDetector)
{
  if (this != &agastDetector){
    AgastProperties::operator=(agastDetector);
    this->initAgastFromProperties();
  }
  return *this;
}

AgastDetector &AgastDetector::operator =(AgastDetector &&agastDetector) noexcept
{
  if (this != &agastDetector){
    AgastProperties::operator=(std::forward<AgastProperties>(agastDetector));
    this->initAgastFromProperties();
  }
  return *this;
}

#if CV_VERSION_MAJOR >= 4
cv::AgastFeatureDetector::DetectorType AgastDetector::convertDetectorType(const QString &detectorType)
{
  cv::AgastFeatureDetector::DetectorType detector_type = cv::AgastFeatureDetector::DetectorType::OAST_9_16;
  if (detectorType.compare("AGAST_5_8") == 0 ) {
    detector_type = cv::AgastFeatureDetector::AGAST_5_8;
  } else if (detectorType.compare("AGAST_7_12d") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12d;
  } else if (detectorType.compare("AGAST_7_12s") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12s;
  }
  return detector_type;
}
#else
int AgastDetector::convertDetectorType(const QString &detectorType)
{
  int detector_type = cv::AgastFeatureDetector::OAST_9_16;
  if (detectorType.compare("AGAST_5_8") == 0 ) {
    detector_type = cv::AgastFeatureDetector::AGAST_5_8;
  } else if (detectorType.compare("AGAST_7_12d") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12d;
  } else if (detectorType.compare("AGAST_7_12s") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12s;
  }
  return detector_type;
}
#endif

void AgastDetector::initAgastFromProperties()
{
  mAgast = cv::AgastFeatureDetector::create(AgastProperties::threshold(),
                                            AgastProperties::nonmaxSuppression(),
                                            convertDetectorType(AgastProperties::detectorType()));
}

bool AgastDetector::detect(const cv::Mat &img,
                           std::vector<cv::KeyPoint> &keyPoints,
                           cv::InputArray &mask)
{

  try {
    mAgast->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("AGAST Detector error: %s", e.what());
    return true;
  }

  return false;
}

void AgastDetector::setThreshold(int threshold)
{
  AgastProperties::setThreshold(threshold);
  mAgast->setThreshold(threshold);
}

void AgastDetector::setNonmaxSuppression(bool nonmaxSuppression)
{
  AgastProperties::setNonmaxSuppression(nonmaxSuppression);
  mAgast->setNonmaxSuppression(nonmaxSuppression);
}

void AgastDetector::setDetectorType(const QString &detectorType)
{
  AgastProperties::setDetectorType(detectorType);
  mAgast->setType(convertDetectorType(AgastProperties::detectorType()));
}

void AgastDetector::reset()
{
  AgastProperties::reset();

  mAgast->setThreshold(AgastProperties::threshold());
  mAgast->setNonmaxSuppression(AgastProperties::nonmaxSuppression());
  mAgast->setType(convertDetectorType(AgastProperties::detectorType()));
}

} // namespace photomatch
