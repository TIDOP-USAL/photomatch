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


#include "akaze.h"

#include <tidop/core/messages.h>


namespace photomatch
{


AkazeProperties::AkazeProperties()
  : mDescriptorType("MLDB"),
    mDescriptorSize(0),
    mDescriptorChannels(3),
    mThreshold(0.001),
    mOctaves(4),
    mOctaveLayers(4),
    mDiffusivity("DIFF_PM_G2")
{
}

AkazeProperties::AkazeProperties(const AkazeProperties &akazeProperties)
  : Akaze(akazeProperties),
    mDescriptorType(akazeProperties.mDescriptorType),
    mDescriptorSize(akazeProperties.mDescriptorSize),
    mDescriptorChannels(akazeProperties.mDescriptorChannels),
    mThreshold(akazeProperties.mThreshold),
    mOctaves(akazeProperties.mOctaves),
    mOctaveLayers(akazeProperties.mOctaveLayers),
    mDiffusivity(akazeProperties.mDiffusivity)
{
}

QString AkazeProperties::descriptorType() const
{
  return mDescriptorType;
}

int AkazeProperties::descriptorSize() const
{
  return mDescriptorSize;
}

int AkazeProperties::descriptorChannels() const
{
  return mDescriptorChannels;
}

double AkazeProperties::threshold() const
{
  return mThreshold;
}

int AkazeProperties::octaves() const
{
  return mOctaves;
}

int AkazeProperties::octaveLayers() const
{
  return mOctaveLayers;
}

QString AkazeProperties::diffusivity() const
{
  return mDiffusivity;
}

void AkazeProperties::setDescriptorType(const QString &descriptorType)
{
  if (descriptorType.compare("KAZE") == 0 ||
      descriptorType.compare("KAZE_UPRIGHT") == 0 ||
      descriptorType.compare("MLDB") == 0 ||
      descriptorType.compare("MLDB_UPRIGHT") == 0){
    mDescriptorType = descriptorType;
  }
}

void AkazeProperties::setDescriptorSize(int descriptorSize)
{
  mDescriptorSize = descriptorSize;
}

void AkazeProperties::setDescriptorChannels(int channels)
{
  mDescriptorChannels = channels;
}

void AkazeProperties::setThreshold(double threshold)
{
  mThreshold = threshold;
}

void AkazeProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void AkazeProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void AkazeProperties::setDiffusivity(const QString &diffusivity)
{
  if (diffusivity.compare("DIFF_PM_G1") == 0 ||
      diffusivity.compare("DIFF_PM_G2") == 0 ||
      diffusivity.compare("DIFF_WEICKERT") == 0 ||
      diffusivity.compare("DIFF_CHARBONNIER") == 0){
    mDiffusivity = diffusivity;
  }
}

void AkazeProperties::reset()
{
  mDescriptorType = "MLDB";
  mDescriptorSize = 0;
  mDescriptorChannels = 3;
  mThreshold = 0.001;
  mOctaves = 4;
  mOctaveLayers = 4;
  mDiffusivity = "DIFF_PM_G2";
}

QString AkazeProperties::name() const
{
  return QString("AKAZE");
}



/*----------------------------------------------------------------*/


AkazeDetectorDescriptor::AkazeDetectorDescriptor()
{
  mAkaze = cv::AKAZE::create(convertDescriptorType(AkazeProperties::descriptorType()),
                             AkazeProperties::descriptorSize(),
                             AkazeProperties::descriptorChannels(),
                             static_cast<float>(AkazeProperties::threshold()),
                             AkazeProperties::octaves(),
                             AkazeProperties::octaveLayers(),
                             convertDiffusivity(AkazeProperties::diffusivity()));
}

AkazeDetectorDescriptor::AkazeDetectorDescriptor(const AkazeDetectorDescriptor &akazeDetectorDescriptor)
  : AkazeProperties(akazeDetectorDescriptor),
    KeypointDetector(akazeDetectorDescriptor),
    DescriptorExtractor(akazeDetectorDescriptor)
{
  mAkaze = cv::AKAZE::create(convertDescriptorType(AkazeProperties::descriptorType()),
                             AkazeProperties::descriptorSize(),
                             AkazeProperties::descriptorChannels(),
                             static_cast<float>(AkazeProperties::threshold()),
                             AkazeProperties::octaves(),
                             AkazeProperties::octaveLayers(),
                             convertDiffusivity(AkazeProperties::diffusivity()));
}

AkazeDetectorDescriptor::AkazeDetectorDescriptor(const QString &descriptorType,
                                                 int descriptorSize,
                                                 int descriptorChannels,
                                                 double threshold,
                                                 int octaves,
                                                 int octaveLayers,
                                                 const QString &diffusivity)
  : mAkaze(cv::AKAZE::create())
{
  setDescriptorType(descriptorType);
  setDescriptorSize(descriptorSize);
  setDescriptorChannels(descriptorChannels);
  setThreshold(threshold);
  setOctaves(octaves);
  setOctaveLayers(octaveLayers);
  setDiffusivity(diffusivity);
}

#if CV_VERSION_MAJOR >= 4
cv::AKAZE::DescriptorType AkazeDetectorDescriptor::convertDescriptorType(const QString &descriptorType)
{
  cv::AKAZE::DescriptorType descriptor_type = cv::AKAZE::DescriptorType::DESCRIPTOR_MLDB;

  if (descriptorType.compare("KAZE") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_KAZE;
  } else if (descriptorType.compare("KAZE_UPRIGHT") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_KAZE_UPRIGHT;
  } else if (descriptorType.compare("MLDB") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_MLDB;
  } else if (descriptorType.compare("MLDB_UPRIGHT") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_MLDB_UPRIGHT;
  }

  return descriptor_type;
}

cv::KAZE::DiffusivityType AkazeDetectorDescriptor::convertDiffusivity(const QString &diffusivity)
{
  cv::KAZE::DiffusivityType diff = cv::KAZE::DiffusivityType::DIFF_PM_G1;

  if (diffusivity.compare("DIFF_PM_G1") == 0){
    diff = cv::KAZE::DIFF_PM_G1;
  } else if (diffusivity.compare("DIFF_PM_G2") == 0){
    diff = cv::KAZE::DIFF_PM_G2;
  } else if (diffusivity.compare("DIFF_WEICKERT") == 0){
    diff = cv::KAZE::DIFF_WEICKERT;
  } else if (diffusivity.compare("DIFF_CHARBONNIER") == 0){
    diff = cv::KAZE::DIFF_CHARBONNIER;
  }

  return diff;
}

#else

int AkazeDetectorDescriptor::convertDescriptorType(const QString &descriptorType)
{
  int descriptor_type = cv::AKAZE::DESCRIPTOR_MLDB;

  if (descriptorType.compare("KAZE") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_KAZE;
  } else if (descriptorType.compare("KAZE_UPRIGHT") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_KAZE_UPRIGHT;
  } else if (descriptorType.compare("MLDB") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_MLDB;
  } else if (descriptorType.compare("MLDB_UPRIGHT") == 0){
    descriptor_type = cv::AKAZE::DESCRIPTOR_MLDB_UPRIGHT;
  }

  return descriptor_type;
}

int AkazeDetectorDescriptor::convertDiffusivity(const QString &diffusivity)
{
  int diff = cv::KAZE::DIFF_PM_G1;

  if (diffusivity.compare("DIFF_PM_G1") == 0){
    diff = cv::KAZE::DIFF_PM_G1;
  } else if (diffusivity.compare("DIFF_PM_G2") == 0){
    diff = cv::KAZE::DIFF_PM_G2;
  } else if (diffusivity.compare("DIFF_WEICKERT") == 0){
    diff = cv::KAZE::DIFF_WEICKERT;
  } else if (diffusivity.compare("DIFF_CHARBONNIER") == 0){
    diff = cv::KAZE::DIFF_CHARBONNIER;
  }

  return diff;
}

#endif

std::vector<cv::KeyPoint> AkazeDetectorDescriptor::detect(const cv::Mat &img, 
                                                          const cv::Mat &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mAkaze->detect(img, keyPoints, mask);
  return keyPoints;
}

cv::Mat AkazeDetectorDescriptor::extract(const cv::Mat &img, 
                                         std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mAkaze->compute(img, keyPoints, descriptors);
  return descriptors;
}

void AkazeDetectorDescriptor::setDescriptorType(const QString &descriptorType)
{
  AkazeProperties::setDescriptorType(descriptorType);
  mAkaze->setDescriptorType(convertDescriptorType(descriptorType));
}

void AkazeDetectorDescriptor::setDescriptorSize(int descriptorSize)
{
  AkazeProperties::setDescriptorSize(descriptorSize);
  mAkaze->setDescriptorSize(descriptorSize);
}

void AkazeDetectorDescriptor::setDescriptorChannels(int channels)
{
  AkazeProperties::setDescriptorChannels(channels);
  mAkaze->setDescriptorChannels(channels);
}

void AkazeDetectorDescriptor::setThreshold(double threshold)
{
  AkazeProperties::setThreshold(threshold);
  mAkaze->setThreshold(threshold);
}

void AkazeDetectorDescriptor::setOctaves(int octaves)
{
  AkazeProperties::setOctaves(octaves);
  mAkaze->setNOctaves(octaves);
}

void AkazeDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  AkazeProperties::setOctaveLayers(octaveLayers);
  mAkaze->setNOctaveLayers(octaveLayers);
}

void AkazeDetectorDescriptor::setDiffusivity(const QString &diffusivity)
{
  AkazeProperties::setDiffusivity(diffusivity);
  mAkaze->setDiffusivity(convertDiffusivity(diffusivity));
}

void AkazeDetectorDescriptor::reset()
{
  AkazeProperties::reset();
  mAkaze->setDescriptorType(convertDescriptorType(AkazeProperties::descriptorType()));
  mAkaze->setDescriptorSize(AkazeProperties::descriptorSize());
  mAkaze->setDescriptorChannels(AkazeProperties::descriptorChannels());
  mAkaze->setThreshold(AkazeProperties::threshold());
  mAkaze->setNOctaves(AkazeProperties::octaves());
  mAkaze->setNOctaveLayers(AkazeProperties::octaveLayers());
  mAkaze->setDiffusivity(convertDiffusivity(AkazeProperties::diffusivity()));
}


} // namespace photomatch
