#include "brisk.h"

#include <tidop/core/messages.h>


namespace fme
{


BriskProperties::BriskProperties()
  : IBrisk(),
    mThreshold(30),
    mOctaves(3),
    mPatternScale(1.0)
{}

BriskProperties::~BriskProperties()
{

}

int BriskProperties::threshold() const
{
  return mThreshold;
}

int BriskProperties::octaves() const
{
  return mOctaves;
}

double BriskProperties::patternScale() const
{
  return mPatternScale;
}

void BriskProperties::setThreshold(int threshold)
{
  mThreshold = threshold;
}

void BriskProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void BriskProperties::setPatternScale(double patternScale)
{
  mPatternScale = patternScale;
}

void BriskProperties::reset()
{
  mThreshold = 30;
  mOctaves = 3;
  mPatternScale = 1.0;
}

QString BriskProperties::name() const
{
  return QString("BRISK");
}


/*----------------------------------------------------------------*/


BriskDetectorDescriptor::BriskDetectorDescriptor()
  : BriskProperties(),
    KeypointDetector(),
    DescriptorExtractor()
{
  update();
}

BriskDetectorDescriptor::BriskDetectorDescriptor(int threshold,
                                                 int octaves,
                                                 double patternScale)
  : BriskProperties(),
    KeypointDetector(),
    DescriptorExtractor()
{
  BriskProperties::setThreshold(threshold);
  BriskProperties::setOctaves(octaves);
  BriskProperties::setPatternScale(patternScale);
  update();
}

BriskDetectorDescriptor::~BriskDetectorDescriptor()
{

}

void BriskDetectorDescriptor::update()
{
  mBrisk = cv::BRISK::create(BriskProperties::threshold(),
                             BriskProperties::octaves(),
                             static_cast<float>(BriskProperties::patternScale()));
}

bool BriskDetectorDescriptor::detect(const cv::Mat &img,
                                     std::vector<cv::KeyPoint> &keyPoints,
                                     cv::InputArray &mask)
{

  try {
    mBrisk->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("BRISK Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool BriskDetectorDescriptor::extract(const cv::Mat &img,
                                      std::vector<cv::KeyPoint> &keyPoints,
                                      cv::Mat &descriptors)
{
  try {
    mBrisk->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("BRISK Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void BriskDetectorDescriptor::setThreshold(int threshold)
{
  BriskProperties::setThreshold(threshold);
  update();
}

void BriskDetectorDescriptor::setOctaves(int octaves)
{
  BriskProperties::setOctaves(octaves);
  update();
}

void BriskDetectorDescriptor::setPatternScale(double patternScale)
{
  BriskProperties::setPatternScale(patternScale);
  update();
}

void BriskDetectorDescriptor::reset()
{
  BriskProperties::reset();
  update();
}

/*----------------------------------------------------------------*/

} // namespace fme
