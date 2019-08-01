#include "gftt.h"

namespace fme
{

GfttProperties::GfttProperties()
  : IGftt(),
    mMaxFeatures(1000),
    mQualityLevel(0.01),
    mMinDistance(1),
    mBlockSize(3),
    mHarrisDetector(false),
    mK(0.04)
{

}

GfttProperties::~GfttProperties()
{

}

int GfttProperties::maxFeatures() const
{
  return mMaxFeatures;
}

double GfttProperties::qualityLevel() const
{
  return mQualityLevel;
}

double GfttProperties::minDistance() const
{
  return mMinDistance;
}

int GfttProperties::blockSize() const
{
  return mBlockSize;
}

bool GfttProperties::harrisDetector() const
{
  return mHarrisDetector;
}

double GfttProperties::k() const
{
  return mK;
}

void GfttProperties::setMaxFeatures(int maxFeatures)
{
  mMaxFeatures = maxFeatures;
}

void GfttProperties::setQualityLevel(double qlevel)
{
  mQualityLevel = qlevel;
}

void GfttProperties::setMinDistance(double minDistance)
{
  mMinDistance = minDistance;
}

void GfttProperties::setBlockSize(int blockSize)
{
  mBlockSize = blockSize;
}

void GfttProperties::setHarrisDetector(bool value)
{
  mHarrisDetector = value;
}

void GfttProperties::setK(double k)
{
  mK = k;
}

void GfttProperties::reset()
{
  mMaxFeatures = 1000;
  mQualityLevel = 0.01;
  mMinDistance = 1;
  mBlockSize = 3;
  mHarrisDetector = false;
  mK = 0.04;
}


/*----------------------------------------------------------------*/


GfttDetector::GfttDetector()
  : GfttProperties(),
    KeypointDetector(),
    mGFTT(cv::GFTTDetector::create())
{
  mGFTT->setMaxFeatures(GfttProperties::maxFeatures());
  mGFTT->setQualityLevel(GfttProperties::qualityLevel());
  mGFTT->setMinDistance(GfttProperties::minDistance());
  mGFTT->setBlockSize(GfttProperties::blockSize());
  mGFTT->setHarrisDetector(GfttProperties::harrisDetector());
  mGFTT->setK(GfttProperties::k());
}

GfttDetector::GfttDetector(int maxFeatures,
                           double qualityLevel,
                           double minDistance,
                           int blockSize,
                           bool harrisDetector,
                           double k)
  : GfttProperties(),
    KeypointDetector(),
    mGFTT(cv::GFTTDetector::create())
{
  setMaxFeatures(maxFeatures);
  setQualityLevel(qualityLevel);
  setMinDistance(minDistance);
  setBlockSize(blockSize);
  setHarrisDetector(harrisDetector);
  setK(k);
}

GfttDetector::~GfttDetector()
{

}

std::vector<cv::KeyPoint> GfttDetector::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mGFTT->detect(img, keyPoints, mask);
  return keyPoints;
}

void GfttDetector::setMaxFeatures(int maxFeatures)
{
  GfttProperties::setMaxFeatures(maxFeatures);
  mGFTT->setMaxFeatures(maxFeatures);
}

void GfttDetector::setQualityLevel(double qlevel)
{
  GfttProperties::setQualityLevel(qlevel);
  mGFTT->setQualityLevel(qlevel);
}

void GfttDetector::setMinDistance(double minDistance)
{
  GfttProperties::setMinDistance(minDistance);
  mGFTT->setMinDistance(minDistance);
}

void GfttDetector::setBlockSize(int blockSize)
{
  GfttProperties::setBlockSize(blockSize);
  mGFTT->setBlockSize(blockSize);
}

void GfttDetector::setHarrisDetector(bool value)
{
  GfttProperties::setHarrisDetector(value);
  mGFTT->setHarrisDetector(value);
}

void GfttDetector::setK(double k)
{
  GfttProperties::setK(k);
  mGFTT->setK(k);
}

void GfttDetector::reset()
{
  GfttProperties::reset();
  mGFTT->setMaxFeatures(GfttProperties::maxFeatures());
  mGFTT->setQualityLevel(GfttProperties::qualityLevel());
  mGFTT->setMinDistance(GfttProperties::minDistance());
  mGFTT->setBlockSize(GfttProperties::blockSize());
  mGFTT->setHarrisDetector(GfttProperties::harrisDetector());
  mGFTT->setK(GfttProperties::k());
}

} // namespace fme