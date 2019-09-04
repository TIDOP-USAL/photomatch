#include "agast.h"

namespace fme
{


AgastProperties::AgastProperties()
  : IAgast(),
    mThreshold(10),
    mNonmaxSuppression(true),
    mDetectorType("OAST_9_16")
{
}

AgastProperties::~AgastProperties()
{
}

int AgastProperties::threshold() const
{
  return mThreshold;
}

bool AgastProperties::nonmaxSuppression() const
{
  return mNonmaxSuppression;
}

QString AgastProperties::detectorType() const
{
  return mDetectorType;
}

void AgastProperties::setThreshold(int threshold)
{
  mThreshold = threshold;
}

void AgastProperties::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression = nonmaxSuppression;
}

void AgastProperties::setDetectorType(const QString &detectorType)
{
  if (detectorType.compare("AGAST_5_8") == 0 ||
      detectorType.compare("AGAST_7_12d") == 0 ||
      detectorType.compare("AGAST_7_12s") == 0 ||
      detectorType.compare("OAST_9_16") == 0) {
    mDetectorType = detectorType;
  }
}

void AgastProperties::reset()
{
  mThreshold = 10;
  mNonmaxSuppression = true;
  mDetectorType = "OAST_9_16";
}

QString AgastProperties::name() const
{
  return QString("AGAST");
}


/*----------------------------------------------------------------*/


AgastDetector::AgastDetector()
  : AgastProperties(),
    KeypointDetector()
{
  int detector_type = cv::AgastFeatureDetector::OAST_9_16;
  QString detectorType = AgastProperties::detectorType();
  if (detectorType.compare("AGAST_5_8") == 0 ) {
    detector_type = cv::AgastFeatureDetector::AGAST_5_8;
  } else if (detectorType.compare("AGAST_7_12d") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12d;
  } else if (detectorType.compare("AGAST_7_12s") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12s;
  }

  mAgast = cv::AgastFeatureDetector::create(AgastProperties::threshold(),
                                            AgastProperties::nonmaxSuppression(),
                                            detector_type);
}

AgastDetector::AgastDetector(int threshold, bool nonmaxSuppression, QString detectorType)
  : AgastProperties(),
    KeypointDetector(),
    mAgast(cv::AgastFeatureDetector::create())
{
  setThreshold(threshold);
  setNonmaxSuppression(nonmaxSuppression);
  setDetectorType(detectorType);
}

AgastDetector::~AgastDetector()
{

}

std::vector<cv::KeyPoint> AgastDetector::detect(const cv::Mat &img, cv::InputArray &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mAgast->detect(img, keyPoints, mask);
  return keyPoints;
}

void AgastDetector::setThreshold(int threshold)
{
  AgastProperties::setThreshold(threshold);
  mAgast->setThreshold(threshold);
}

void AgastDetector::setNonmaxSuppression(bool nonmaxSuppression)
{
  AgastProperties::setNonmaxSuppression(nonmaxSuppression);
  mAgast->setNonmaxSuppression(nonmaxSuppression);
}

void AgastDetector::setDetectorType(const QString &detectorType)
{
  AgastProperties::setDetectorType(detectorType);
  int detector_type = cv::AgastFeatureDetector::OAST_9_16;
  if (detectorType.compare("AGAST_5_8") == 0 ) {
    detector_type = cv::AgastFeatureDetector::AGAST_5_8;
  } else if (detectorType.compare("AGAST_7_12d") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12d;
  } else if (detectorType.compare("AGAST_7_12s") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12s;
  }
  mAgast->setType(detector_type);
}

void AgastDetector::reset()
{
  AgastProperties::reset();

  mAgast->setThreshold(AgastProperties::threshold());
  mAgast->setNonmaxSuppression(AgastProperties::nonmaxSuppression());
  setDetectorType(AgastProperties::detectorType());
}


} // namespace fme
