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


#ifndef PHOTOMATCH_SURF_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_SURF_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

#include <opencv2/xfeatures2d.hpp>
#ifdef HAVE_OPENCV_CUDAFEATURES2D
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#endif // HAVE_OPENCV_CUDAFEATURES2D


namespace photomatch
{


/*!
 * \brief SURF detector/descriptor properties class
 */
class PHOTOMATCH_EXPORT SurfProperties
  : public Surf
{

public:

  SurfProperties();
  SurfProperties(const SurfProperties &surfProperties);
  ~SurfProperties() override = default;

// Surf interface

public:

  double hessianThreshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  bool extendedDescriptor() const override;
  bool upright() const override;
  void setHessianThreshold(double hessianThreshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setExtendedDescriptor(bool extendedDescriptor) override;
  void setUpright(bool upright) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  double mHessianThreshold;
  int mOctaves;
  int mOctaveLayers;
  bool mExtendedDescriptor;
  bool mUpright;
};


/*----------------------------------------------------------------*/

#ifdef OPENCV_ENABLE_NONFREE

class PHOTOMATCH_EXPORT SurfDetectorDescriptor
  : public SurfProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  SurfDetectorDescriptor();
  SurfDetectorDescriptor(const SurfDetectorDescriptor &surfDetectorDescriptor);
  SurfDetectorDescriptor(double hessianThreshold,
                         int octaves,
                         int octaveLayers,
                         bool extendedDescriptor,
                         bool upright);
  ~SurfDetectorDescriptor() override = default;

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// Surf interface

public:

  void setHessianThreshold(double hessianThreshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setExtendedDescriptor(bool extendedDescriptor) override;
  void setUpright(bool upright) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::SURF> mSurf;
};


/*----------------------------------------------------------------*/

#ifdef HAVE_OPENCV_CUDAFEATURES2D

class PHOTOMATCH_EXPORT SurfCudaDetectorDescriptor
  : public SurfProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  SurfCudaDetectorDescriptor();
  SurfCudaDetectorDescriptor(const SurfCudaDetectorDescriptor &surfDetectorDescriptor);
  SurfCudaDetectorDescriptor(double hessianThreshold,
                             int octaves,
                             int octaveLayers,
                             bool extendedDescriptor,
                             bool upright);
  ~SurfCudaDetectorDescriptor() override = default;

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// Surf interface

public:

  void setHessianThreshold(double hessianThreshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setExtendedDescriptor(bool extendedDescriptor) override;
  void setUpright(bool upright) override;

// Feature interface

public:

  void reset() override;

protected:

  std::unique_ptr<cv::cuda::SURF_CUDA> mSurf;
};


#endif // HAVE_OPENCV_CUDAFEATURES2D

#endif // OPENCV_ENABLE_NONFREE

} // namespace photomatch

#endif // PHOTOMATCH_SURF_DETECTOR_DESCRIPTOR_H
