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


#ifndef PHOTOMATCH_AKAZE_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_AKAZE_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


/*!
 * \brief AKAZE detector/descriptor properties class
 */
class PHOTOMATCH_EXPORT AkazeProperties
  : public Akaze
{

public:

  AkazeProperties();
  AkazeProperties(const AkazeProperties &akazeProperties);
  ~AkazeProperties() override;

// IAkaze interface

public:

  virtual QString descriptorType() const override;
  virtual int descriptorSize() const override;
  virtual int descriptorChannels() const override;
  virtual double threshold() const override;
  virtual int octaves() const override;
  virtual int octaveLayers() const override;
  virtual QString diffusivity() const override;
  virtual void setDescriptorType(const QString &descriptorType) override;
  virtual void setDescriptorSize(int descriptorSize) override;
  virtual void setDescriptorChannels(int channels) override;
  virtual void setThreshold(double threshold) override;
  virtual void setOctaves(int octaves) override;
  virtual void setOctaveLayers(int octaveLayers) override;
  virtual void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  QString mDescriptorType;
  int mDescriptorSize;
  int mDescriptorChannels;
  double mThreshold;
  int mOctaves;
  int mOctaveLayers;
  QString mDiffusivity;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT AkazeDetectorDescriptor
  : public AkazeProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  AkazeDetectorDescriptor();
  AkazeDetectorDescriptor(const AkazeDetectorDescriptor &akazeDetectorDescriptor);
  AkazeDetectorDescriptor(const QString &descriptorType,
                          int descriptorSize,
                          int descriptorChannels,
                          double threshold,
                          int octaves,
                          int octaveLayers,
                          QString diffusivity);

  ~AkazeDetectorDescriptor() override;

private:

#if CV_VERSION_MAJOR >= 4
  cv::AKAZE::DescriptorType convertDescriptorType(const QString &descriptorType);
  cv::KAZE::DiffusivityType convertDiffusivity(const QString &descriptorType);
#else
  int convertDescriptorType(const QString &descriptorType);
  int convertDiffusivity(const QString &diffusivity);
#endif

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


// IAkaze interface

public:

  void setDescriptorType(const QString &descriptorType) override;
  void setDescriptorSize(int descriptorSize) override;
  void setDescriptorChannels(int channels) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::AKAZE> mAkaze;

};

} // namespace photomatch

#endif // PHOTOMATCH_AKAZE_DETECTOR_DESCRIPTOR_H
