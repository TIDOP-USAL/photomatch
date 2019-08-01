#include "sift.h"


namespace fme
{


/*----------------------------------------------------------------*/


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


/*----------------------------------------------------------------*/



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

std::vector<cv::KeyPoint> SiftDetectorDescriptor::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mSift->detect(img, keyPoints, mask);
  return keyPoints;
}

cv::Mat SiftDetectorDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mSift->compute(img, keyPoints, descriptors);
  return descriptors;
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

/*----------------------------------------------------------------*/

} // namespace fme







