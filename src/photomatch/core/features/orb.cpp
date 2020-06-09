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


#include "orb.h"

#include <tidop/core/messages.h>


namespace photomatch
{


OrbProperties::OrbProperties()
  : Orb(),
    mFeaturesNumber(5000),
    mScaleFactor(1.2),
    mLevelsNumber(8),
    mEdgeThreshold(31),
    mFirstLevel(0),
    mWTA_K(2),
    mScoreType("Harris"),
    mPatchSize(31),
    mFastThreshold(20)
{
}

OrbProperties::OrbProperties(const OrbProperties &orbProperties)
  : Orb(orbProperties),
    mFeaturesNumber(orbProperties.mFeaturesNumber),
    mScaleFactor(orbProperties.mScaleFactor),
    mLevelsNumber(orbProperties.mLevelsNumber),
    mEdgeThreshold(orbProperties.mEdgeThreshold),
    mFirstLevel(orbProperties.mFirstLevel),
    mWTA_K(orbProperties.mWTA_K),
    mScoreType(orbProperties.mScoreType),
    mPatchSize(orbProperties.mPatchSize),
    mFastThreshold(orbProperties.mFastThreshold)
{
}

int OrbProperties::featuresNumber() const
{
  return mFeaturesNumber;
}

double OrbProperties::scaleFactor() const
{
  return mScaleFactor;
}

int OrbProperties::levelsNumber() const
{
  return mLevelsNumber;
}

int OrbProperties::edgeThreshold() const
{
  return mEdgeThreshold;
}

int OrbProperties::firstLevel() const
{
  return mFirstLevel;
}

int OrbProperties::wta_k() const
{
  return mWTA_K;
}

QString OrbProperties::scoreType() const
{
  return mScoreType;
}

int OrbProperties::patchSize() const
{
  return mPatchSize;
}

int OrbProperties::fastThreshold() const
{
  return mFastThreshold;
}

void OrbProperties::setScaleFactor(double scaleFactor)
{
  mScaleFactor = scaleFactor;
}

void OrbProperties::setFeaturesNumber(int featuresNumber)
{
  mFeaturesNumber = featuresNumber;
}

void OrbProperties::setLevelsNumber(int levelsNumber)
{
  mLevelsNumber = levelsNumber;
}

void OrbProperties::setEdgeThreshold(int edgeThreshold)
{
  mEdgeThreshold = edgeThreshold;
}

void OrbProperties::setFirstLevel(int firstLevel)
{
  mFirstLevel = firstLevel;
}

void OrbProperties::setWTA_K(int WTA_K)
{
  mWTA_K = WTA_K;
}

void OrbProperties::setScoreType(const QString &scoreType)
{
  mScoreType = scoreType;
}

void OrbProperties::setPatchSize(int patchSize)
{
  mPatchSize = patchSize;
}

void OrbProperties::setFastThreshold(int fastThreshold)
{
  mFastThreshold = fastThreshold;
}

void OrbProperties::reset()
{
  mFeaturesNumber = 5000;
  mScaleFactor = 1.2;
  mLevelsNumber = 8;
  mEdgeThreshold = 31;
  mFirstLevel = 0;
  mWTA_K = 2;
  mScoreType = "Harris";
  mPatchSize = 31;
  mFastThreshold = 20;
}

QString OrbProperties::name() const
{
  return QString("ORB");
}


/*----------------------------------------------------------------*/


OrbDetectorDescriptor::OrbDetectorDescriptor()
{
  mOrb = cv::ORB::create(OrbProperties::featuresNumber(),
                         static_cast<float>(OrbProperties::scaleFactor()),
                         OrbProperties::levelsNumber(),
                         OrbProperties::edgeThreshold(),
                         OrbProperties::firstLevel(),
                         OrbProperties::wta_k(),
                         convertScoreType(OrbProperties::scoreType()),
                         OrbProperties::patchSize(),
                         OrbProperties::fastThreshold());
}

OrbDetectorDescriptor::OrbDetectorDescriptor(const OrbDetectorDescriptor &orbDetectorDescriptor)
  : OrbProperties(orbDetectorDescriptor),
    KeypointDetector(orbDetectorDescriptor),
    DescriptorExtractor(orbDetectorDescriptor)
{
  mOrb = cv::ORB::create(OrbProperties::featuresNumber(),
                         static_cast<float>(OrbProperties::scaleFactor()),
                         OrbProperties::levelsNumber(),
                         OrbProperties::edgeThreshold(),
                         OrbProperties::firstLevel(),
                         OrbProperties::wta_k(),
                         convertScoreType(OrbProperties::scoreType()),
                         OrbProperties::patchSize(),
                         OrbProperties::fastThreshold());
}

OrbDetectorDescriptor::OrbDetectorDescriptor(int featuresNumber,
                                             double scaleFactor,
                                             int levelsNumber,
                                             int edgeThreshold,
                                             int wta_k,
                                             const QString &scoreType,
                                             int patchSize,
                                             int fastThreshold)
  : mOrb(cv::ORB::create())
{
  setFeaturesNumber(featuresNumber);
  setScaleFactor(scaleFactor);
  setLevelsNumber(levelsNumber);
  setEdgeThreshold(edgeThreshold);
  setWTA_K(wta_k);
  setScoreType(scoreType);
  setPatchSize(patchSize);
  setFastThreshold(fastThreshold);
}

#if CV_VERSION_MAJOR >= 4

cv::ORB::ScoreType OrbDetectorDescriptor::convertScoreType(const QString &scoreType)
{
  cv::ORB::ScoreType score = cv::ORB::ScoreType::HARRIS_SCORE;

  if (scoreType.compare("Harris") == 0){
    score = cv::ORB::HARRIS_SCORE;
  } else if (scoreType.compare("FAST") == 0){
    score = cv::ORB::FAST_SCORE;
  }

  return score;
}

#else

int OrbDetectorDescriptor::convertScoreType(const QString &scoreType)
{
  int score = cv::ORB::HARRIS_SCORE;

  if (scoreType.compare("Harris") == 0){
    score = cv::ORB::HARRIS_SCORE;
  } else if (scoreType.compare("FAST") == 0){
    score = cv::ORB::FAST_SCORE;
  }

  return score;
}
#endif

bool OrbDetectorDescriptor::detect(const cv::Mat &img,
                                   std::vector<cv::KeyPoint> &keyPoints,
                                   cv::InputArray &mask)
{

  try {
    mOrb->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("ORB Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool OrbDetectorDescriptor::extract(const cv::Mat &img,
                                    std::vector<cv::KeyPoint> &keyPoints,
                                    cv::Mat &descriptors)
{

  try {
    mOrb->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("ORB Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void OrbDetectorDescriptor::setFeaturesNumber(int featuresNumber)
{
  OrbProperties::setFeaturesNumber(featuresNumber);
  mOrb->setMaxFeatures(featuresNumber);
}

void OrbDetectorDescriptor::setScaleFactor(double scaleFactor)
{
  OrbProperties::setScaleFactor(scaleFactor);
  mOrb->setScaleFactor(scaleFactor);
}

void OrbDetectorDescriptor::setLevelsNumber(int levelsNumber)
{
  OrbProperties::setLevelsNumber(levelsNumber);
  mOrb->setNLevels(levelsNumber);
}

void OrbDetectorDescriptor::setEdgeThreshold(int edgeThreshold)
{
  OrbProperties::setEdgeThreshold(edgeThreshold);
  mOrb->setEdgeThreshold(edgeThreshold);
}

void OrbDetectorDescriptor::setFirstLevel(int firstLevel)
{
  OrbProperties::setFirstLevel(firstLevel);
  mOrb->setFirstLevel(firstLevel);
}

void OrbDetectorDescriptor::setWTA_K(int WTA_K)
{
  OrbProperties::setWTA_K(WTA_K);
  mOrb->setWTA_K(WTA_K);
}

void OrbDetectorDescriptor::setScoreType(const QString &scoreType)
{
  OrbProperties::setScoreType(scoreType);
  mOrb->setScoreType(convertScoreType(scoreType));
}

void OrbDetectorDescriptor::setPatchSize(int patchSize)
{
  OrbProperties::setPatchSize(patchSize);
  mOrb->setPatchSize(patchSize);
}

void OrbDetectorDescriptor::setFastThreshold(int fastThreshold)
{
  OrbProperties::setFastThreshold(fastThreshold);
  mOrb->setFastThreshold(fastThreshold);
}

void OrbDetectorDescriptor::reset()
{
  OrbProperties::reset();
  mOrb->setMaxFeatures(OrbProperties::featuresNumber());
  mOrb->setScaleFactor(OrbProperties::scaleFactor());
  mOrb->setNLevels(OrbProperties::levelsNumber());
  mOrb->setEdgeThreshold(OrbProperties::edgeThreshold());
  mOrb->setFirstLevel(OrbProperties::firstLevel());
  mOrb->setWTA_K(OrbProperties::wta_k());
  mOrb->setScoreType(convertScoreType(OrbProperties::scoreType()));
  mOrb->setPatchSize(OrbProperties::patchSize());
  mOrb->setFastThreshold(OrbProperties::fastThreshold());
}


/*----------------------------------------------------------------*/


#ifdef HAVE_OPENCV_CUDAFEATURES2D

OrbCudaDetectorDescriptor::OrbCudaDetectorDescriptor()
{
  update();
}

OrbCudaDetectorDescriptor::OrbCudaDetectorDescriptor(const OrbCudaDetectorDescriptor &orbCudaDetectorDescriptor)
  : OrbProperties(orbCudaDetectorDescriptor),
    KeypointDetector(orbCudaDetectorDescriptor),
    DescriptorExtractor(orbCudaDetectorDescriptor)
{
  update();
}

OrbCudaDetectorDescriptor::OrbCudaDetectorDescriptor(int featuresNumber,
                                                     double scaleFactor,
                                                     int levelsNumber,
                                                     int edgeThreshold,
                                                     int wta_k,
                                                     const QString &scoreType,
                                                     int patchSize,
                                                     int fastThreshold)
{
  setFeaturesNumber(featuresNumber);
  setScaleFactor(scaleFactor);
  setLevelsNumber(levelsNumber);
  setEdgeThreshold(edgeThreshold);
  setWTA_K(wta_k);
  setScoreType(scoreType);
  setPatchSize(patchSize);
  setFastThreshold(fastThreshold);
}

#if CV_VERSION_MAJOR >= 4

cv::ORB::ScoreType OrbCudaDetectorDescriptor::convertScoreType(const QString &scoreType)
{
  cv::ORB::ScoreType score = cv::ORB::ScoreType::HARRIS_SCORE;

  if (scoreType.compare("Harris") == 0){
    score = cv::ORB::HARRIS_SCORE;
  } else if (scoreType.compare("FAST") == 0){
    score = cv::ORB::FAST_SCORE;
  }

  return score;
}

#else

int OrbCudaDetectorDescriptor::convertScoreType(const QString &scoreType)
{
  int score = cv::ORB::HARRIS_SCORE;

  if (scoreType.compare("Harris") == 0){
    score = cv::ORB::HARRIS_SCORE;
  } else if (scoreType.compare("FAST") == 0){
    score = cv::ORB::FAST_SCORE;
  }

  return score;
}
#endif

void OrbCudaDetectorDescriptor::update()
{
  mOrb = cv::cuda::ORB::create(OrbProperties::featuresNumber(),
                               static_cast<float>(OrbProperties::scaleFactor()),
                               OrbProperties::levelsNumber(),
                               OrbProperties::edgeThreshold(),
                               OrbProperties::firstLevel(),
                               OrbProperties::wta_k(),
                               convertScoreType(OrbProperties::scoreType()),
                               OrbProperties::patchSize(),
                               OrbProperties::fastThreshold());
}

bool OrbCudaDetectorDescriptor::detect(const cv::Mat &img,
                                       std::vector<cv::KeyPoint> &keyPoints,
                                       cv::InputArray &mask)
{
  try {
    cv::cuda::GpuMat g_img(img);
    cv::cuda::GpuMat g_mask(mask);
    mOrb->detect(g_img, keyPoints, g_mask);
  } catch (cv::Exception &e) {
    msgError("ORB Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool OrbCudaDetectorDescriptor::extract(const cv::Mat &img,
                                        std::vector<cv::KeyPoint> &keyPoints,
                                        cv::Mat &descriptors)
{
  try {
    cv::cuda::GpuMat g_img(img);
    cv::cuda::GpuMat g_descriptors;
    mOrb->compute(g_img, keyPoints, g_descriptors);
    g_descriptors.download(descriptors);
  } catch (cv::Exception &e) {
    msgError("ORB Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void OrbCudaDetectorDescriptor::setFeaturesNumber(int featuresNumber)
{
  OrbProperties::setFeaturesNumber(featuresNumber);
  update();
}

void OrbCudaDetectorDescriptor::setScaleFactor(double scaleFactor)
{
  OrbProperties::setScaleFactor(scaleFactor);
  update();
}

void OrbCudaDetectorDescriptor::setLevelsNumber(int levelsNumber)
{
  OrbProperties::setLevelsNumber(levelsNumber);
  update();
}

void OrbCudaDetectorDescriptor::setEdgeThreshold(int edgeThreshold)
{
  OrbProperties::setEdgeThreshold(edgeThreshold);
  update();
}

void OrbCudaDetectorDescriptor::setFirstLevel(int firstLevel)
{
  OrbProperties::setFirstLevel(firstLevel);
  update();
}

void OrbCudaDetectorDescriptor::setWTA_K(int WTA_K)
{
  OrbProperties::setWTA_K(WTA_K);
  update();
}

void OrbCudaDetectorDescriptor::setScoreType(const QString &scoreType)
{
  OrbProperties::setScoreType(scoreType);
  update();
}

void OrbCudaDetectorDescriptor::setPatchSize(int patchSize)
{
  OrbProperties::setPatchSize(patchSize);
  update();
}

void OrbCudaDetectorDescriptor::setFastThreshold(int fastThreshold)
{
  OrbProperties::setFastThreshold(fastThreshold);
  update();
}

void OrbCudaDetectorDescriptor::reset()
{
  OrbProperties::reset();
  update();
}

#endif // HAVE_OPENCV_CUDAFEATURES2D

} // namespace photomatch

