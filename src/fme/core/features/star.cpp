#include "star.h"

namespace fme
{


StarProperties::StarProperties()
  : IStar(),
    mMaxSize(45),
    mResponseThreshold(30),
    mLineThresholdProjected(10),
    mLineThresholdBinarized(8),
    mSuppressNonmaxSize(5)
{}

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


/*----------------------------------------------------------------*/


StarDetector::StarDetector()
  : StarProperties(),
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

std::vector<cv::KeyPoint> StarDetector::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mSTAR->detect(img, keyPoints, mask);
  return keyPoints;
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


/*----------------------------------------------------------------*/


} // namespace fme
