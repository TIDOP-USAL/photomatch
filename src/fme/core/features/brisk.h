#ifndef FME_BRISK_DETECTOR_DESCRIPTOR_H
#define FME_BRISK_DETECTOR_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{


/*----------------------------------------------------------------*/


class FME_EXPORT BriskProperties
  : public IBrisk
{
public:

  BriskProperties();
  ~BriskProperties() override;

// IBrisk interface

public:

  virtual int threshold() const override;
  virtual int octaves() const override;
  virtual double patternScale() const override;
  virtual void setThreshold(int threshold) override;
  virtual void setOctaves(int octaves) override;
  virtual void setPatternScale(double patternScale) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mThreshold;
  int mOctaves;
  double mPatternScale;
};


/*----------------------------------------------------------------*/


class FME_EXPORT BriskDetectorDescriptor
  : public BriskProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  BriskDetectorDescriptor();
  BriskDetectorDescriptor(int threshold,
                          int octaves,
                          double patternScale);

  ~BriskDetectorDescriptor() override;

protected:

  void update();


// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// IAkaze interface

public:

  void setThreshold(int threshold) override;
  void setOctaves(int octaves) override;
  void setPatternScale(double patternScale) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::BRISK> mBrisk;

};


/*----------------------------------------------------------------*/


} // namespace fme

#endif // FME_BRISK_DETECTOR_DESCRIPTOR_H
