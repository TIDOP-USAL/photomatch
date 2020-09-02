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


#ifndef PHOTOMATCH_SIFT_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_SIFT_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

//#ifdef HAVE_CUDA
//#include "SiftGPU/SiftGPU.h"
//#endif // HAVE_CUDA

#include <QString>

namespace photomatch
{


/*!
 * \brief SIFT detector/descriptor properties class
 */
class PHOTOMATCH_EXPORT SiftProperties
  : public Sift
{

public:

  SiftProperties();
  SiftProperties(const SiftProperties &siftProperties);
  ~SiftProperties() override = default;

// Sift interface

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
};


/*----------------------------------------------------------------*/

#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE

class PHOTOMATCH_EXPORT SiftDetectorDescriptor
  : public SiftProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  SiftDetectorDescriptor();
  SiftDetectorDescriptor(const SiftDetectorDescriptor &siftDetectorDescriptor);
  SiftDetectorDescriptor(int featuresNumber,
                         int octaveLayers,
                         double contrastThreshold,
                         double edgeThreshold,
                         double sigma);
  ~SiftDetectorDescriptor() override = default;

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

// Sift interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::SIFT> mSift;
};

#endif

/*----------------------------------------------------------------*/

//#ifdef HAVE_CUDA


//class SiftCudaDetectorDescriptor
//  : public SiftProperties,
//    public KeypointDetector,
//    public DescriptorExtractor
//{

//public:

//  SiftCudaDetectorDescriptor();
//  SiftCudaDetectorDescriptor(const SiftDetectorDescriptor &siftDetectorDescriptor);
//  SiftCudaDetectorDescriptor(int featuresNumber,
//                             int octaveLayers,
//                             double contrastThreshold,
//                             double edgeThreshold,
//                             double sigma);
//  ~SiftCudaDetectorDescriptor() override = default;

//private:

//  void update();

//// KeypointDetector interface

//public:

//  bool detect(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints, cv::InputArray &mask) override;

//// DescriptorExtractor interface

//public:

//  bool extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints, cv::Mat &descriptors) override;

//// Sift interface

//public:

//  void setFeaturesNumber(int featuresNumber) override;
//  void setOctaveLayers(int octaveLayers) override;
//  void setContrastThreshold(double contrastThreshold) override;
//  void setEdgeThreshold(double edgeThreshold) override;
//  void setSigma(double sigma) override;

//// Feature interface

//public:

//  void reset() override;

//protected:


//};

//#endif // HAVE_CUDA

} // namespace photomatch

#endif // PHOTOMATCH_SIFT_DETECTOR_DESCRIPTOR_H
