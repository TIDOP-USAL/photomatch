#ifndef PHOTOMATCH_FAST_DETECTOR_H
#define PHOTOMATCH_FAST_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT FastProperties
  : public IFast
{
public:

  FastProperties();
  FastProperties(const FastProperties &fastProperties);
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
  QString name() const final;

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
  FastDetector(const FastDetector &fastDetector);
  FastDetector(int threshold, bool nonmaxSuppression, const QString &detectorType);
  ~FastDetector() override;

private:

#if CV_VERSION_MAJOR >= 4
  cv::FastFeatureDetector::DetectorType convertDetectorType(const QString &detectorType);
#else
  int convertDetectorType(const QString &detectorType);
#endif
// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

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


} // namespace photomatch

#endif // PHOTOMATCH_AGAST_DETECTOR_H
