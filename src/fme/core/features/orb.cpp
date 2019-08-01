#include "orb.h"

namespace fme
{


OrbProperties::OrbProperties()
  : IOrb(),
    mFeaturesNumber(5000),
    mScaleFactor(1.2),
    mLevelsNumber(8),
    mEdgeThreshold(31),
    mWTA_K(2),
    mScoreType("Harris"),
    mPatchSize(31),
    mFastThreshold(20)
{}

OrbProperties::~OrbProperties()
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
  mWTA_K = 2;
  mScoreType = "Harris";
  mPatchSize = 31;
  mFastThreshold = 20;
}

/*----------------------------------------------------------------*/


OrbDetectorDescriptor::OrbDetectorDescriptor()
  : OrbProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mOrb(cv::ORB::create())
{
  mOrb->setMaxFeatures(OrbProperties::featuresNumber());
  mOrb->setScaleFactor(OrbProperties::scaleFactor());
  mOrb->setNLevels(OrbProperties::levelsNumber());
  mOrb->setEdgeThreshold(OrbProperties::edgeThreshold());
  mOrb->setWTA_K(OrbProperties::wta_k());
  int score = 0;
  if (OrbProperties::scoreType().compare("Harris") == 0){
    score = 0;
  } else if (OrbProperties::scoreType().compare("FAST") == 0){
    score = 2;
  }
  mOrb->setScoreType(score);
  OrbProperties::setPatchSize(OrbProperties::patchSize());
  mOrb->setFastThreshold(OrbProperties::fastThreshold());
}

OrbDetectorDescriptor::OrbDetectorDescriptor(int featuresNumber,
                                             double scaleFactor,
                                             int levelsNumber,
                                             int edgeThreshold,
                                             int wta_k,
                                             QString scoreType,
                                             int patchSize,
                                             int fastThreshold)
  : OrbProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mOrb(cv::ORB::create())
{
  OrbProperties::setFeaturesNumber(featuresNumber);
  OrbProperties::setScaleFactor(scaleFactor);
  OrbProperties::setLevelsNumber(levelsNumber);
  OrbProperties::setEdgeThreshold(edgeThreshold);
  OrbProperties::setWTA_K(wta_k);
  OrbProperties::setScoreType(scoreType);
  OrbProperties::setPatchSize(patchSize);
  OrbProperties::setFastThreshold(fastThreshold);
}

OrbDetectorDescriptor::~OrbDetectorDescriptor()
{

}

std::vector<cv::KeyPoint> OrbDetectorDescriptor::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mOrb->detect(img, keyPoints, mask);
  return keyPoints;
}

cv::Mat OrbDetectorDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mOrb->compute(img, keyPoints, descriptors);
  return descriptors;
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

void OrbDetectorDescriptor::setWTA_K(int WTA_K)
{
  OrbProperties::setWTA_K(WTA_K);
  mOrb->setWTA_K(WTA_K);
}

void OrbDetectorDescriptor::setScoreType(const QString &scoreType)
{
  OrbProperties::setScoreType(scoreType);
  int score = 0;
  if (scoreType.compare("Harris") == 0){
    score = 0;
  } else if (scoreType.compare("FAST") == 0){
    score = 1;
  }
  mOrb->setScoreType(score);
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
  mOrb->setWTA_K(OrbProperties::wta_k());
  int score = 0;
  if (OrbProperties::scoreType().compare("Harris") == 0){
    score = 0;
  } else if (OrbProperties::scoreType().compare("FAST") == 0){
    score = 2;
  }
  mOrb->setScoreType(score);
  mOrb->setPatchSize(OrbProperties::patchSize());
  mOrb->setFastThreshold(OrbProperties::fastThreshold());
}

/*----------------------------------------------------------------*/

} // namespace fme







