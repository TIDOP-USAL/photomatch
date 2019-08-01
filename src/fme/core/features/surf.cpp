#include "surf.h"

namespace fme
{


/*----------------------------------------------------------------*/



SurfProperties::SurfProperties()
  : ISurf(),
    mHessianThreshold(100),
    mOctaves(4),
    mOctaveLayers(3),
    mExtendedDescriptor(false),
    mRotatedFeatures(false)
{
}

SurfProperties::~SurfProperties()
{
}

double SurfProperties::hessianThreshold() const
{
  return mHessianThreshold;
}

void SurfProperties::setHessianThreshold(double hessianThreshold)
{
  mHessianThreshold = hessianThreshold;
}

int SurfProperties::octaves() const
{
  return mOctaves;
}

void SurfProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

int SurfProperties::octaveLayers() const
{
  return mOctaveLayers;
}

void SurfProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

bool SurfProperties::extendedDescriptor() const
{
  return mExtendedDescriptor;
}

void SurfProperties::setExtendedDescriptor(bool extendedDescriptor)
{
  mExtendedDescriptor = extendedDescriptor;
}

bool SurfProperties::rotatedFeatures() const
{
  return mRotatedFeatures;
}

void SurfProperties::setRotatedFeatures(bool rotatedFeatures)
{
  mRotatedFeatures = rotatedFeatures;
}

void SurfProperties::reset()
{
  mHessianThreshold = 100;
  mOctaves = 4;
  mOctaveLayers = 3;
  mExtendedDescriptor = false;
  mRotatedFeatures = false;
}


/*----------------------------------------------------------------*/


SurfDetectorDescriptor::SurfDetectorDescriptor()
  : SurfProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mSurf(cv::xfeatures2d::SURF::create())
{
  mSurf->setHessianThreshold(SurfProperties::hessianThreshold());
  mSurf->setNOctaves(SurfProperties::octaves());
  mSurf->setNOctaveLayers(SurfProperties::octaveLayers());
  mSurf->setExtended(SurfProperties::extendedDescriptor());
  mSurf->setUpright(SurfProperties::rotatedFeatures());
}

SurfDetectorDescriptor::SurfDetectorDescriptor(double hessianThreshold,
                                               int octaves,
                                               int octaveLayers,
                                               bool extendedDescriptor,
                                               bool rotatedFeatures)
  : SurfProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mSurf(cv::xfeatures2d::SURF::create())
{
  setHessianThreshold(hessianThreshold);
  setOctaves(octaves);
  setOctaveLayers(octaveLayers);
  setExtendedDescriptor(extendedDescriptor);
  setRotatedFeatures(rotatedFeatures);
}

std::vector<cv::KeyPoint> SurfDetectorDescriptor::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mSurf->detect(img, keyPoints, mask);
  return keyPoints;
}

cv::Mat SurfDetectorDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mSurf->compute(img, keyPoints, descriptors);
  return descriptors;
}

SurfDetectorDescriptor::~SurfDetectorDescriptor()
{

}

void SurfDetectorDescriptor::setHessianThreshold(double hessianThreshold)
{
  SurfProperties::setHessianThreshold(hessianThreshold);
  mSurf->setHessianThreshold(hessianThreshold);
}

void SurfDetectorDescriptor::setOctaves(int octaves)
{
  SurfProperties::setOctaves(octaves);
  mSurf->setNOctaves(octaves);
}

void SurfDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  SurfProperties::setOctaveLayers(octaveLayers);
  mSurf->setNOctaveLayers(octaveLayers);
}

void SurfDetectorDescriptor::setExtendedDescriptor(bool extendedDescriptor)
{
  SurfProperties::setExtendedDescriptor(extendedDescriptor);
  mSurf->setExtended(extendedDescriptor);
}

void SurfDetectorDescriptor::setRotatedFeatures(bool rotatedFeatures)
{
  SurfProperties::setRotatedFeatures(rotatedFeatures);
  mSurf->setUpright(rotatedFeatures);
}

void SurfDetectorDescriptor::reset()
{
  SurfProperties::reset();
  mSurf->setHessianThreshold(SurfProperties::hessianThreshold());
  mSurf->setNOctaves(SurfProperties::octaves());
  mSurf->setNOctaveLayers(SurfProperties::octaveLayers());
  mSurf->setExtended(SurfProperties::extendedDescriptor());
  mSurf->setUpright(SurfProperties::rotatedFeatures());

}

/*----------------------------------------------------------------*/

} // namespace fme







