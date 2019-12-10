#include "gftt.h"

#include <tidop/core/messages.h>


namespace photomatch
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

GfttProperties::GfttProperties(const GfttProperties &gfttProperties)
  : IGftt(),
    mMaxFeatures(gfttProperties.mMaxFeatures),
    mQualityLevel(gfttProperties.mQualityLevel),
    mMinDistance(gfttProperties.mMinDistance),
    mBlockSize(gfttProperties.mBlockSize),
    mHarrisDetector(gfttProperties.mHarrisDetector),
    mK(gfttProperties.mK)
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

QString GfttProperties::name() const
{
  return QString("GFTT");
}


/*----------------------------------------------------------------*/


GfttDetector::GfttDetector()
  : GfttProperties(),
    KeypointDetector()
{
  mGFTT = cv::GFTTDetector::create(GfttProperties::maxFeatures(),
                                   GfttProperties::qualityLevel(),
                                   GfttProperties::minDistance(),
                                   GfttProperties::blockSize(),
                                   GfttProperties::harrisDetector(),
                                   GfttProperties::k());
}

GfttDetector::GfttDetector(const GfttDetector &gfttDetector)
  : GfttProperties(gfttDetector),
    KeypointDetector()
{
  mGFTT = cv::GFTTDetector::create(GfttProperties::maxFeatures(),
                                   GfttProperties::qualityLevel(),
                                   GfttProperties::minDistance(),
                                   GfttProperties::blockSize(),
                                   GfttProperties::harrisDetector(),
                                   GfttProperties::k());
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

bool GfttDetector::detect(const cv::Mat &img,
                          std::vector<cv::KeyPoint> &keyPoints,
                          cv::InputArray &mask)
{

  try {
    mGFTT->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("GFTT Detector error: %s", e.what());
    return true;
  }

  return false;
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

} // namespace photomatch
