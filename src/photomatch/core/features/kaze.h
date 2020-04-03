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


#ifndef PHOTOMATCH_KAZE_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_KAZE_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT KazeProperties
  : public Kaze
{
public:

  KazeProperties();
  KazeProperties(const KazeProperties &kazeProperties);
  ~KazeProperties() override = default;

// IKaze interface

public:

  bool extendedDescriptor() const override;
  bool uprightDescriptor() const override;
  double threshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  QString diffusivity() const override;
  void setExtendedDescriptor(bool extended) override;
  void setUprightDescriptor(bool uprightDescriptor) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  bool mExtended;
  bool mUpright;
  double mThreshold;
  int mOctaves;
  int mOctaveLayers;
  QString mDiffusivity;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KazeDetectorDescriptor
  : public KazeProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  KazeDetectorDescriptor();
  KazeDetectorDescriptor(const KazeDetectorDescriptor &kazeDetectorDescriptor);
  KazeDetectorDescriptor(bool extendedDescriptor,
                         bool uprightDescriptor,
                         double threshold,
                         int octaves,
                         int octaveLayers,
                         const QString &diffusivity);

  ~KazeDetectorDescriptor() override = default;

private:

#if CV_VERSION_MAJOR >= 4
  cv::KAZE::DiffusivityType convertDiffusivity(const QString &diffusivity);
#else
  int convertDiffusivity(const QString &diffusivity);
#endif
  void updateCvKaze();

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

// IKaze interface

public:

  void setExtendedDescriptor(bool extended) override;
  void setUprightDescriptor(bool uprightDescriptor) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::KAZE> mKaze;
};

} // namespace photomatch

#endif // PHOTOMATCH_KAZE_DETECTOR_DESCRIPTOR_H
