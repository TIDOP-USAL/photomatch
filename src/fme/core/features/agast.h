#ifndef FME_AGAST_DETECTOR_H
#define FME_AGAST_DETECTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{


/*!
 * \brief AGAST detector properties class
 */
class FME_EXPORT AgastProperties
  : public IAgast
{

public:

  AgastProperties();
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

private:

  int mThreshold;
  bool mNonmaxSuppression;
  QString mDetectorType;

};


/*----------------------------------------------------------------*/


class FME_EXPORT AgastDetector
  : public AgastProperties,
    public KeypointDetector
{

public:

  AgastDetector();
  AgastDetector(int threshold, bool nonmaxSuppression, QString detectorType);
  ~AgastDetector() override;

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img, cv::InputArray &mask) override;

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


} // namespace fme

#endif // FME_AGAST_DETECTOR_H
