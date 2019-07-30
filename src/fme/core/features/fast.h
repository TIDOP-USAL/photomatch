#ifndef FME_FAST_DETECTOR_H
#define FME_FAST_DETECTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{


/*----------------------------------------------------------------*/


class FME_EXPORT FastProperties
  : public IFast
{
public:

  FastProperties();
  ~FastProperties() override;

// IFast interface

public:

  virtual int threshold() const override;
  virtual bool nonmaxSuppression() const override;
  virtual QString detectorType() const override;
  virtual void setThreshold(int threshold) override;
  virtual void setNonmaxSuppression(bool nonmaxSuppression) override;
  virtual void setDetectorType(QString detectorType) override;

// Feature interface

public:

  void reset() override;

private:

  int mThreshold;
  bool mNonmaxSuppression;
  QString mDetectorType;
};


/*----------------------------------------------------------------*/


class FastDetector
  : public FastProperties,
    public KeypointDetector
{

public:

  FastDetector();
  FastDetector(int threshold, bool nonmaxSuppression, const QString &detectorType);
  ~FastDetector() override;

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img, cv::InputArray &mask) override;

// IFast interface

public:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(QString detectorType) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::FastFeatureDetector> mFast;

};


/*----------------------------------------------------------------*/


} // namespace fme

#endif // FME_AGAST_DETECTOR_H
