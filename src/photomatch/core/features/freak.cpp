#include "freak.h"

#include <tidop/core/messages.h>


namespace photomatch
{


FreakProperties::FreakProperties()
  : IFreak(),
    mOrientationNormalized(true),
    mScaleNormalized(true),
    mPatternScale(22.),
    mOctaves(4)
{}

FreakProperties::FreakProperties(const FreakProperties &freakProperties)
  : IFreak(),
    mOrientationNormalized(freakProperties.mOrientationNormalized),
    mScaleNormalized(freakProperties.mScaleNormalized),
    mPatternScale(freakProperties.mPatternScale),
    mOctaves(freakProperties.mOctaves)
{}

FreakProperties::~FreakProperties()
{

}

bool FreakProperties::orientationNormalized() const
{
  return mOrientationNormalized;
}

bool FreakProperties::scaleNormalized() const
{
  return mScaleNormalized;
}

double FreakProperties::patternScale() const
{
  return mPatternScale;
}

int FreakProperties::octaves() const
{
  return mOctaves;
}

void FreakProperties::setOrientationNormalized(bool orientationNormalized)
{
  mOrientationNormalized = orientationNormalized;
}

void FreakProperties::setScaleNormalized(bool scaleNormalized)
{
  mScaleNormalized = scaleNormalized;
}

void FreakProperties::setPatternScale(double patternScale)
{
  mPatternScale = patternScale;
}

void FreakProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void FreakProperties::reset()
{
  mOrientationNormalized = true;
  mScaleNormalized = true;
  mPatternScale = 22.;
  mOctaves = 4;
}

QString FreakProperties::name() const
{
  return QString("FREAK");
}


/*----------------------------------------------------------------*/


FreakDescriptor::FreakDescriptor()
  : FreakProperties(),
    DescriptorExtractor()
{
  update();
}

FreakDescriptor::FreakDescriptor(const FreakDescriptor &freakDescriptor)
  : FreakProperties(freakDescriptor),
    DescriptorExtractor()
{
  update();
}


FreakDescriptor::FreakDescriptor(bool orientationNormalized,
                                 bool scaleNormalized,
                                 double patternScale,
                                 int octaves)
  : FreakProperties(),
    DescriptorExtractor()
{
  FreakProperties::setOrientationNormalized(orientationNormalized);
  FreakProperties::setScaleNormalized(scaleNormalized);
  FreakProperties::setPatternScale(patternScale);
  FreakProperties::setOctaves(octaves);
  update();
}

FreakDescriptor::~FreakDescriptor()
{

}

void FreakDescriptor::update()
{
  mFREAK = cv::xfeatures2d::FREAK::create(FreakProperties::orientationNormalized(),
                                          FreakProperties::scaleNormalized(),
                                          static_cast<float>(FreakProperties::patternScale()),
                                          FreakProperties::octaves());
}

bool FreakDescriptor::extract(const cv::Mat &img,
                              std::vector<cv::KeyPoint> &keyPoints,
                              cv::Mat &descriptors)
{

  try {
    mFREAK->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("FREAK Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void FreakDescriptor::setOrientationNormalized(bool orientationNormalized)
{
  FreakProperties::setOrientationNormalized(orientationNormalized);
  update();
}

void FreakDescriptor::setScaleNormalized(bool scaleNormalized)
{
  FreakProperties::setScaleNormalized(scaleNormalized);
  update();
}

void FreakDescriptor::setPatternScale(double patternScale)
{
  FreakProperties::setPatternScale(patternScale);
  update();
}

void FreakDescriptor::setOctaves(int octaves)
{
  FreakProperties::setOctaves(octaves);
  update();
}

void FreakDescriptor::reset()
{
  FreakProperties::reset();
  update();
}


} // namespace photomatch
