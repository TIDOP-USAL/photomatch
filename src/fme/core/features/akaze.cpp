#include "akaze.h"

namespace fme
{


/*----------------------------------------------------------------*/


AkazeProperties::AkazeProperties()
  : IAkaze(),
    mDescriptorType("MLDB"),
    mDescriptorSize(0),
    mDescriptorChannels(3),
    mThreshold(0.001),
    mOctaves(4),
    mOctaveLayers(4),
    mDiffusivity("DIFF_PM_G2")
{
}

AkazeProperties::~AkazeProperties()
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



/*----------------------------------------------------------------*/


AkazeDetectorDescriptor::AkazeDetectorDescriptor()
  : AkazeProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mAkaze(cv::AKAZE::create())
{
  setDescriptorType(AkazeProperties::descriptorType());
  setDescriptorSize(AkazeProperties::descriptorSize());
  setDescriptorChannels(AkazeProperties::descriptorChannels());
  setThreshold(AkazeProperties::threshold());
  setOctaves(AkazeProperties::octaves());
  setOctaveLayers(AkazeProperties::octaveLayers());
  setDiffusivity(AkazeProperties::diffusivity());
}

AkazeDetectorDescriptor::AkazeDetectorDescriptor(const QString &descriptorType,
                                                 int descriptorSize,
                                                 int descriptorChannels,
                                                 double threshold,
                                                 int octaves,
                                                 int octaveLayers,
                                                 QString diffusivity)
  : AkazeProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mAkaze(cv::AKAZE::create())
{
  setDescriptorType(descriptorType);
  setDescriptorSize(descriptorSize);
  setDescriptorChannels(descriptorChannels);
  setThreshold(threshold);
  setOctaves(octaves);
  setOctaveLayers(octaveLayers);
  setDiffusivity(diffusivity);
}

AkazeDetectorDescriptor::~AkazeDetectorDescriptor()
{

}

std::vector<cv::KeyPoint> AkazeDetectorDescriptor::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mAkaze->detect(img, keyPoints, mask);
  return keyPoints;
}

cv::Mat AkazeDetectorDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mAkaze->compute(img, keyPoints, descriptors);
  return descriptors;
}

void AkazeDetectorDescriptor::setDescriptorType(const QString &descriptorType)
{
  AkazeProperties::setDescriptorType(descriptorType);

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
  mAkaze->setDescriptorType(descriptor_type);
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
  mAkaze->setDiffusivity(diff);
}

void AkazeDetectorDescriptor::reset()
{
  AkazeProperties::reset();
  setDescriptorType(AkazeProperties::descriptorType());
  mAkaze->setDescriptorSize(AkazeProperties::descriptorSize());
  mAkaze->setDescriptorChannels(AkazeProperties::descriptorChannels());
  mAkaze->setThreshold(AkazeProperties::threshold());
  mAkaze->setNOctaves(AkazeProperties::octaves());
  mAkaze->setNOctaveLayers(AkazeProperties::octaveLayers());
  setDiffusivity(AkazeProperties::diffusivity());
}


/*----------------------------------------------------------------*/


} // namespace fme