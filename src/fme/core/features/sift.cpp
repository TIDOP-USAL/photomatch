#include "sift.h"

#include <tidop/core/messages.h>


namespace fme
{


SiftProperties::SiftProperties()
  : ISift(),
    mFeaturesNumber(5000),
    mOctaveLayers(3),
    mContrastThreshold(0.04),
    mEdgeThreshold(10.),
    mSigma(1.6)
{}

SiftProperties::~SiftProperties() {}

int SiftProperties::featuresNumber() const
{
  return mFeaturesNumber;
}

int SiftProperties::octaveLayers() const
{
  return mOctaveLayers;
}

double SiftProperties::contrastThreshold() const
{
  return mContrastThreshold;
}

double SiftProperties::edgeThreshold() const
{
  return mEdgeThreshold;
}

double SiftProperties::sigma() const
{
  return mSigma;
}

void SiftProperties::setFeaturesNumber(int featuresNumber)
{
  mFeaturesNumber = featuresNumber;
}

void SiftProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void SiftProperties::setContrastThreshold(double contrastThreshold)
{
  mContrastThreshold = contrastThreshold;
}

void SiftProperties::setEdgeThreshold(double edgeThreshold)
{
  mEdgeThreshold = edgeThreshold;
}

void SiftProperties::setSigma(double sigma)
{
  mSigma = sigma;
}

void SiftProperties::reset()
{
  mFeaturesNumber = 5000;
  mOctaveLayers = 3;
  mContrastThreshold = 0.04;
  mEdgeThreshold = 10.;
  mSigma = 1.6;
}

QString SiftProperties::name() const
{
  return QString("SIFT");
}


/*----------------------------------------------------------------*/

#ifdef OPENCV_ENABLE_NONFREE

SiftDetectorDescriptor::SiftDetectorDescriptor()
  : SiftProperties(),
    KeypointDetector(),
    DescriptorExtractor()
{ 
  update();
}

SiftDetectorDescriptor::SiftDetectorDescriptor(int featuresNumber,
                                               int octaveLayers,
                                               double contrastThreshold,
                                               double edgeThreshold,
                                               double sigma)
  : SiftProperties(),
    KeypointDetector(),
    DescriptorExtractor()
{
  SiftProperties::setFeaturesNumber(featuresNumber);
  SiftProperties::setOctaveLayers(octaveLayers);
  SiftProperties::setContrastThreshold(contrastThreshold);
  SiftProperties::setEdgeThreshold(edgeThreshold);
  SiftProperties::setSigma(sigma);
  update();
}

SiftDetectorDescriptor::~SiftDetectorDescriptor()
{

}

void SiftDetectorDescriptor::update()
{
  mSift = cv::xfeatures2d::SIFT::create(SiftProperties::featuresNumber(),
                                        SiftProperties::octaveLayers(),
                                        SiftProperties::contrastThreshold(),
                                        SiftProperties::edgeThreshold(),
                                        SiftProperties::sigma());
}

bool SiftDetectorDescriptor::detect(const cv::Mat &img,
                                    std::vector<cv::KeyPoint> &keyPoints,
                                    cv::InputArray &mask)
{

  try {
    mSift->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("SIFT Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool SiftDetectorDescriptor::extract(const cv::Mat &img,
                                     std::vector<cv::KeyPoint> &keyPoints,
                                     cv::Mat &descriptors)
{

  try {
    mSift->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("SIFT Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void SiftDetectorDescriptor::setFeaturesNumber(int featuresNumber)
{
  SiftProperties::setFeaturesNumber(featuresNumber);
  update();
}

void SiftDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  SiftProperties::setOctaveLayers(octaveLayers);
  update();
}

void SiftDetectorDescriptor::setContrastThreshold(double contrastThreshold)
{
  SiftProperties::setContrastThreshold(contrastThreshold);
  update();
}

void SiftDetectorDescriptor::setEdgeThreshold(double edgeThreshold)
{
  SiftProperties::setEdgeThreshold(edgeThreshold);
  update();
}

void SiftDetectorDescriptor::setSigma(double sigma)
{
  SiftProperties::setSigma(sigma);
  update();
}

void SiftDetectorDescriptor::reset()
{
  SiftProperties::reset();
  update();
}

#endif

} // namespace fme







