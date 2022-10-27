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


#ifndef PHOTOMATCH_ASIFT_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_ASIFT_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"
#include "asift/aff_features2d.hpp"

#if defined OPENCV_ENABLE_NONFREE && defined HAVE_OPENCV_XFEATURES2D
#include <opencv2/xfeatures2d.hpp>
#endif // HAVE_OPENCV_XFEATURES2D

#include <QString>

namespace photomatch
{


/*!
 * \brief ASIFT detector/descriptor properties class
 */
class PHOTOMATCH_EXPORT ASiftProperties
  : public ASift
{

public:

  ASiftProperties();
  ASiftProperties(const ASiftProperties &asiftProperties);
  ~ASiftProperties() override = default;

// ASift interface

public:

  int featuresNumber() const override;
  int octaveLayers() const override;
  double contrastThreshold() const override;
  double edgeThreshold() const override;
  double sigma() const override;
  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;
  int minTilt() const override;
  int maxTilt() const override;
  void setMinTilt(int minTilt) override;
  void setMaxTilt(int maxTilt) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mFeaturesNumber;
  int mOctaveLayers;
  double mContrastThreshold;
  double mEdgeThreshold;
  double mSigma;
  int mMinTilt;
  int mMaxTilt;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT ASiftDetectorDescriptor
  : public ASiftProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  ASiftDetectorDescriptor();
  ASiftDetectorDescriptor(const ASiftDetectorDescriptor &asiftDetectorDescriptor);
  ASiftDetectorDescriptor(int featuresNumber,
                          int octaveLayers,
                          double contrastThreshold,
                          double edgeThreshold,
                          double sigma,
                          int minTilt,
                          int maxTilt);
  ~ASiftDetectorDescriptor() override = default;

private:

  void update();

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img,
                                   const cv::Mat &mask = cv::Mat()) override;

// DescriptorExtractor interface

public:

  cv::Mat extract(const cv::Mat &img,
                  std::vector<cv::KeyPoint> &keyPoints) override;

// ASift interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;
  void setMinTilt(int minTilt) override;
  void setMaxTilt(int maxTilt) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::affma::AffFeatureDetector> mDetector;
  cv::Ptr<cv::affma::AffDescriptorExtractor> mDescriptor;
};


} // namespace photomatch

#endif // PHOTOMATCH_ASIFT_DETECTOR_DESCRIPTOR_H
