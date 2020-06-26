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


#ifndef PHOTOMATCH_ORB_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_ORB_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#if defined HAVE_CUDA && defined HAVE_OPENCV_CUDAFEATURES2D
#include <opencv2/cudafeatures2d.hpp>
#endif // HAVE_OPENCV_CUDAFEATURES2D

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT OrbProperties
  : public Orb
{
public:

  OrbProperties();
  OrbProperties(const OrbProperties &orbProperties);
  ~OrbProperties() override = default;

// Orb interface

public:

  int featuresNumber() const override;
  double scaleFactor() const override;
  int levelsNumber() const override;
  int edgeThreshold() const override;
  int firstLevel() const override;
  int wta_k() const override;
  QString scoreType() const override;
  int patchSize() const override;
  int fastThreshold() const override;
  void setFeaturesNumber(int featuresNumber) override;
  void setScaleFactor(double scaleFactor) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setFirstLevel(int firstLevel) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mFeaturesNumber;
  double mScaleFactor;
  int mLevelsNumber;
  int mEdgeThreshold;
  int mFirstLevel;
  int mWTA_K;
  QString mScoreType;
  int mPatchSize;
  int mFastThreshold;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT OrbDetectorDescriptor
  : public OrbProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  OrbDetectorDescriptor();
  OrbDetectorDescriptor(const OrbDetectorDescriptor &orbDetectorDescriptor);
  OrbDetectorDescriptor(int featuresNumber,
                        double scaleFactor,
                        int levelsNumber,
                        int edgeThreshold,
                        int wta_k,
                        const QString &scoreType,
                        int patchSize,
                        int fastThreshold);
  ~OrbDetectorDescriptor() override = default;

private:

#if CV_VERSION_MAJOR >= 4
  cv::ORB::ScoreType convertScoreType(const QString &scoreType);
#else
  int convertScoreType(const QString &scoreType);
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

// Orb interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setScaleFactor(double scaleFactor) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setFirstLevel(int firstLevel) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::ORB> mOrb;
};



/*----------------------------------------------------------------*/

#if defined HAVE_CUDA && defined HAVE_OPENCV_CUDAFEATURES2D

class PHOTOMATCH_EXPORT OrbCudaDetectorDescriptor
  : public OrbProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  OrbCudaDetectorDescriptor();
  OrbCudaDetectorDescriptor(const OrbCudaDetectorDescriptor &orbCudaDetectorDescriptor);
  OrbCudaDetectorDescriptor(int featuresNumber,
                            double scaleFactor,
                            int levelsNumber,
                            int edgeThreshold,
                            int wta_k,
                            const QString &scoreType,
                            int patchSize,
                            int fastThreshold);

  ~OrbCudaDetectorDescriptor() override = default;

private:

//#if CV_VERSION_MAJOR >= 4
//  cv::ORB::ScoreType convertScoreType(const QString &scoreType);
//#else
  int convertScoreType(const QString &scoreType);
//#endif

  void update();

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

// Orb interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setScaleFactor(double scaleFactor) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setFirstLevel(int firstLevel) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::cuda::ORB> mOrb;
};

#endif // HAVE_OPENCV_CUDAFEATURES2D

} // namespace photomatch



#endif // PHOTOMATCH_ORB_DETECTOR_DESCRIPTOR_H
