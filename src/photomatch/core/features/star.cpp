#include "star.h"

#include <tidop/core/messages.h>


namespace photomatch
{


StarProperties::StarProperties()
  : IStar(),
    mMaxSize(45),
    mResponseThreshold(30),
    mLineThresholdProjected(10),
    mLineThresholdBinarized(8),
    mSuppressNonmaxSize(5)
{
}

StarProperties::StarProperties(const StarProperties &starProperties)
  : IStar(),
    mMaxSize(starProperties.mMaxSize),
    mResponseThreshold(starProperties.mResponseThreshold),
    mLineThresholdProjected(starProperties.mLineThresholdProjected),
    mLineThresholdBinarized(starProperties.mLineThresholdBinarized),
    mSuppressNonmaxSize(starProperties.mSuppressNonmaxSize)
{
}

StarProperties::~StarProperties()
{
}

int StarProperties::maxSize() const
{
  return mMaxSize;
}

int StarProperties::responseThreshold() const
{
  return mResponseThreshold;
}

int StarProperties::lineThresholdProjected() const
{
  return mLineThresholdProjected;
}

int StarProperties::lineThresholdBinarized() const
{
  return mLineThresholdBinarized;
}

int StarProperties::suppressNonmaxSize() const
{
  return mSuppressNonmaxSize;
}

void StarProperties::setMaxSize(int maxSize)
{
  mMaxSize = maxSize;
}

void StarProperties::setResponseThreshold(int responseThreshold)
{
  mResponseThreshold = responseThreshold;
}

void StarProperties::setLineThresholdProjected(int lineThresholdProjected)
{
  mLineThresholdProjected = lineThresholdProjected;
}

void StarProperties::setLineThresholdBinarized(int lineThresholdBinarized)
{
  mLineThresholdBinarized = lineThresholdBinarized;
}

void StarProperties::setSuppressNonmaxSize(int suppressNonmaxSize)
{
  mSuppressNonmaxSize = suppressNonmaxSize;
}

void StarProperties::reset()
{
  mMaxSize = 45;
  mResponseThreshold = 30;
  mLineThresholdProjected = 10;
  mLineThresholdBinarized = 8;
  mSuppressNonmaxSize = 5;
}

QString StarProperties::name() const
{
  return QString("STAR");
}


/*----------------------------------------------------------------*/


StarDetector::StarDetector()
  : StarProperties(),
    KeypointDetector()
{
  update();
}

StarDetector::StarDetector(const StarDetector &starDetector)
  : StarProperties(starDetector),
    KeypointDetector()
{
  update();
}

StarDetector::StarDetector(int maxSize,
                           int responseThreshold,
                           int lineThresholdProjected,
                           int lineThresholdBinarized,
                           int suppressNonmaxSize)
  : StarProperties(),
    KeypointDetector()
{
  StarProperties::setMaxSize(maxSize);
  StarProperties::setResponseThreshold(responseThreshold);
  StarProperties::setLineThresholdProjected(lineThresholdProjected);
  StarProperties::setLineThresholdBinarized(lineThresholdBinarized);
  StarProperties::setSuppressNonmaxSize(suppressNonmaxSize);
  update();
}

StarDetector::~StarDetector()
{

}

void StarDetector::update()
{
  mSTAR = cv::xfeatures2d::StarDetector::create(StarProperties::maxSize(),
                                                StarProperties::responseThreshold(),
                                                StarProperties::lineThresholdProjected(),
                                                StarProperties::lineThresholdBinarized(),
                                                StarProperties::suppressNonmaxSize());
}

bool StarDetector::detect(const cv::Mat &img,
                          std::vector<cv::KeyPoint> &keyPoints,
                          cv::InputArray &mask)
{

  try {
    mSTAR->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("STAR Detector error: %s", e.what());
    return true;
  }

  return false;
}

void StarDetector::setMaxSize(int maxSize)
{
  StarProperties::setMaxSize(maxSize);
  update();
}

void StarDetector::setResponseThreshold(int responseThreshold)
{
  StarProperties::setResponseThreshold(responseThreshold);
  update();
}

void StarDetector::setLineThresholdProjected(int lineThresholdProjected)
{
  StarProperties::setLineThresholdProjected(lineThresholdProjected);
  update();
}

void StarDetector::setLineThresholdBinarized(int lineThresholdBinarized)
{
  StarProperties::setLineThresholdBinarized(lineThresholdBinarized);
  update();
}

void StarDetector::setSuppressNonmaxSize(int suppressNonmaxSize)
{
  StarProperties::setSuppressNonmaxSize(suppressNonmaxSize);
  update();
}

void StarDetector::reset()
{
  StarProperties::reset();
  update();
}


} // namespace photomatch
