#ifndef PHOTOMATCH_AGAST_DETECTOR_H
#define PHOTOMATCH_AGAST_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


/*!
 * \brief AGAST detector properties class
 */
class PHOTOMATCH_EXPORT AgastProperties
  : public IAgast
{

public:

  AgastProperties();
  AgastProperties(const AgastProperties &agast);
  ~AgastProperties() override;

// IAgast interface

public:

  virtual int threshold() const override;
  virtual bool nonmaxSuppression() const override;
  virtual QString detectorType() const override;
  virtual void setThreshold(int threshold) override;
  virtual void setNonmaxSuppression(bool nonmaxSuppression) override;
  virtual void setDetectorType(const QString &detectorType) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  int mThreshold;
  bool mNonmaxSuppression;
  QString mDetectorType;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT AgastDetector
  : public AgastProperties,
    public KeypointDetector
{

public:

  AgastDetector();
  AgastDetector(const AgastDetector &agastDetector);
  AgastDetector(int threshold, bool nonmaxSuppression, QString detectorType);
  ~AgastDetector() override;

private:

#if CV_VERSION_MAJOR >= 4
  cv::AgastFeatureDetector::DetectorType convertDetectorType(const QString &detectorType);
#else
  int convertDetectorType(const QString &detectorType);
#endif

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// IAgast interface

public:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(const QString &detectorType) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::AgastFeatureDetector> mAgast;

};


} // namespace photomatch

#endif // PHOTOMATCH_AGAST_DETECTOR_H
