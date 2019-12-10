#include "agast.h"

#include <tidop/core/messages.h>


namespace photomatch
{


AgastProperties::AgastProperties()
  : IAgast(),
    mThreshold(10),
    mNonmaxSuppression(true),
    mDetectorType("OAST_9_16")
{
}

AgastProperties::AgastProperties(const AgastProperties &agast)
  : IAgast(),
    mThreshold(agast.mThreshold),
    mNonmaxSuppression(agast.nonmaxSuppression()),
    mDetectorType(agast.mDetectorType)
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
  mAgast = cv::AgastFeatureDetector::create(AgastProperties::threshold(),
                                            AgastProperties::nonmaxSuppression(),
                                            convertDetectorType(AgastProperties::detectorType()));
}

AgastDetector::AgastDetector(const AgastDetector &agastDetector)
  : AgastProperties(agastDetector),
    KeypointDetector()
{
  mAgast = cv::AgastFeatureDetector::create(AgastProperties::threshold(),
                                            AgastProperties::nonmaxSuppression(),
                                            convertDetectorType(AgastProperties::detectorType()));
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

#if CV_VERSION_MAJOR >= 4
cv::AgastFeatureDetector::DetectorType AgastDetector::convertDetectorType(const QString &detectorType)
{
  cv::AgastFeatureDetector::DetectorType detector_type = cv::AgastFeatureDetector::DetectorType::OAST_9_16;
  if (detectorType.compare("AGAST_5_8") == 0 ) {
    detector_type = cv::AgastFeatureDetector::AGAST_5_8;
  } else if (detectorType.compare("AGAST_7_12d") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12d;
  } else if (detectorType.compare("AGAST_7_12s") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12s;
  }
  return detector_type;
}
#else
int AgastDetector::convertDetectorType(const QString &detectorType)
{
  int detector_type = cv::AgastFeatureDetector::OAST_9_16;
  if (detectorType.compare("AGAST_5_8") == 0 ) {
    detector_type = cv::AgastFeatureDetector::AGAST_5_8;
  } else if (detectorType.compare("AGAST_7_12d") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12d;
  } else if (detectorType.compare("AGAST_7_12s") == 0){
    detector_type = cv::AgastFeatureDetector::AGAST_7_12s;
  }
  return detector_type;
}
#endif

bool AgastDetector::detect(const cv::Mat &img,
                           std::vector<cv::KeyPoint> &keyPoints,
                           cv::InputArray &mask)
{

  try {
    mAgast->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("AGAST Detector error: %s", e.what());
    return true;
  }

  return false;
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
  mAgast->setType(convertDetectorType(AgastProperties::detectorType()));
}

void AgastDetector::reset()
{
  AgastProperties::reset();

  mAgast->setThreshold(AgastProperties::threshold());
  mAgast->setNonmaxSuppression(AgastProperties::nonmaxSuppression());
  mAgast->setType(convertDetectorType(AgastProperties::detectorType()));
}


} // namespace photomatch
