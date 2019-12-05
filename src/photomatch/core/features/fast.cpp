#include "fast.h"

#include <tidop/core/messages.h>


namespace photomatch
{


FastProperties::FastProperties()
  : IFast(),
    mThreshold(10),
    mNonmaxSuppression(true),
    mDetectorType("TYPE_9_16")
{
}

FastProperties::FastProperties(const FastProperties &fastProperties)
  : IFast(),
    mThreshold(fastProperties.mThreshold),
    mNonmaxSuppression(fastProperties.mNonmaxSuppression),
    mDetectorType(fastProperties.mDetectorType)
{
}

FastProperties::~FastProperties()
{
}

int FastProperties::threshold() const
{
  return mThreshold;
}

bool FastProperties::nonmaxSuppression() const
{
  return mNonmaxSuppression;
}

QString FastProperties::detectorType() const
{
  return mDetectorType;
}

void FastProperties::setThreshold(int threshold)
{
  mThreshold = threshold;
}

void FastProperties::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression = nonmaxSuppression;
}

void FastProperties::setDetectorType(QString detectorType)
{
  mDetectorType = detectorType;
}

void FastProperties::reset()
{
  mThreshold = 10;
  mNonmaxSuppression = true;
  mDetectorType = "TYPE_9_16";
}

QString FastProperties::name() const
{
  return QString("FAST");
}


/*----------------------------------------------------------------*/


FastDetector::FastDetector()
  : FastProperties(),
    KeypointDetector()
{
  mFast = cv::FastFeatureDetector::create(FastProperties::threshold(),
                                          FastProperties::nonmaxSuppression(),
                                          convertDetectorType(FastProperties::detectorType()));
}

FastDetector::FastDetector(const FastDetector &fastDetector)
  : FastProperties(fastDetector),
    KeypointDetector()
{
  mFast = cv::FastFeatureDetector::create(FastProperties::threshold(),
                                          FastProperties::nonmaxSuppression(),
                                          convertDetectorType(FastProperties::detectorType()));
}

FastDetector::FastDetector(int threshold, bool nonmaxSuppression, const QString &detectorType)
  : FastProperties(),
    KeypointDetector(),
    mFast(cv::FastFeatureDetector::create())
{
  setThreshold(threshold);
  setNonmaxSuppression(nonmaxSuppression);
  setDetectorType(detectorType);
}

FastDetector::~FastDetector()
{

}

#if CV_VERSION_MAJOR >= 4
cv::FastFeatureDetector::DetectorType FastDetector::convertDetectorType(const QString &detectorType)
{
  cv::FastFeatureDetector::DetectorType type = cv::FastFeatureDetector::DetectorType::TYPE_9_16;

  if (detectorType.compare("TYPE_5_8") == 0){
    type = cv::FastFeatureDetector::TYPE_5_8;
  } else if (detectorType.compare("TYPE_7_12") == 0) {
    type = cv::FastFeatureDetector::TYPE_7_12;
  } else if (detectorType.compare("TYPE_9_16") == 0) {
    type = cv::FastFeatureDetector::TYPE_9_16;
  }

  return type;
}

#else

int FastDetector::convertDetectorType(const QString &detectorType)
{
  int type = cv::FastFeatureDetector::TYPE_9_16;

  if (detectorType.compare("TYPE_5_8") == 0){
    type = cv::FastFeatureDetector::TYPE_5_8;
  } else if (detectorType.compare("TYPE_7_12") == 0) {
    type = cv::FastFeatureDetector::TYPE_7_12;
  } else if (detectorType.compare("TYPE_9_16") == 0) {
    type = cv::FastFeatureDetector::TYPE_9_16;
  }

  return type;
}
#endif

bool FastDetector::detect(const cv::Mat &img,
                          std::vector<cv::KeyPoint> &keyPoints,
                          cv::InputArray &mask)
{

  try {
    mFast->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("FAST Detector error: %s", e.what());
    return true;
  }

  return false;
}

void FastDetector::setThreshold(int threshold)
{
  FastProperties::setThreshold(threshold);
  mFast->setThreshold(threshold);
}

void FastDetector::setNonmaxSuppression(bool nonmaxSuppression)
{
  FastProperties::setNonmaxSuppression(nonmaxSuppression);
  mFast->setNonmaxSuppression(nonmaxSuppression);
}

void FastDetector::setDetectorType(QString detectorType)
{
  FastProperties::setDetectorType(detectorType);
  mFast->setType(convertDetectorType(detectorType));
}

void FastDetector::reset()
{
  FastProperties::reset();
  mFast->setThreshold(FastProperties::threshold());
  mFast->setNonmaxSuppression(FastProperties::nonmaxSuppression());
  mFast->setType(convertDetectorType(FastProperties::detectorType()));
}


} // namespace photomatch
