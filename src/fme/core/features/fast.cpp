#include "fast.h"

namespace fme
{

/*----------------------------------------------------------------*/

FastProperties::FastProperties()
  : IFast(),
    mThreshold(10),
    mNonmaxSuppression(true),
    mDetectorType("TYPE_9_16")
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
    KeypointDetector(),
    mFast(cv::FastFeatureDetector::create())
{
  mFast->setThreshold(FastProperties::threshold());
  mFast->setNonmaxSuppression(FastProperties::nonmaxSuppression());
  int type = cv::FastFeatureDetector::TYPE_9_16;
  QString detectorType = FastProperties::detectorType();
  if (detectorType.compare("TYPE_5_8") == 0){
    type = cv::FastFeatureDetector::TYPE_5_8;
  } else if (detectorType.compare("TYPE_7_12") == 0) {
    type = cv::FastFeatureDetector::TYPE_7_12;
  } else if (detectorType.compare("TYPE_9_16") == 0) {
    type = cv::FastFeatureDetector::TYPE_9_16;
  }
  mFast->setType(type);
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

std::vector<cv::KeyPoint> FastDetector::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mFast->detect(img, keyPoints, mask);
  return keyPoints;
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
  int type = cv::FastFeatureDetector::TYPE_9_16;
  if (detectorType.compare("TYPE_5_8") == 0){
    type = cv::FastFeatureDetector::TYPE_5_8;
  } else if (detectorType.compare("TYPE_7_12") == 0) {
    type = cv::FastFeatureDetector::TYPE_7_12;
  } else if (detectorType.compare("TYPE_9_16") == 0) {
    type = cv::FastFeatureDetector::TYPE_9_16;
  }
  mFast->setType(type);
}

void FastDetector::reset()
{
  FastProperties::reset();

  mFast->setThreshold(FastProperties::threshold());
  mFast->setNonmaxSuppression(FastProperties::nonmaxSuppression());
  setDetectorType(FastProperties::detectorType());
}


/*----------------------------------------------------------------*/


} // namespace fme
