#ifndef FME_SURF_DETECTOR_DESCRIPTOR_H
#define FME_SURF_DETECTOR_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

#include <opencv2/xfeatures2d.hpp>

namespace fme
{

/*----------------------------------------------------------------*/


/*!
 * \brief SURF detector/descriptor properties class
 */
class FME_EXPORT SurfProperties
  : public ISurf
{

public:

  SurfProperties();
  ~SurfProperties() override;

  // ISurf interface

public:

  virtual double hessianThreshold() const override;
  virtual int octaves() const override;
  virtual int octaveLayers() const override;
  virtual bool extendedDescriptor() const override;
  virtual bool rotatedFeatures() const override;
  virtual void setHessianThreshold(double hessianThreshold) override;
  virtual void setOctaves(int octaves) override;
  virtual void setOctaveLayers(int octaveLayers) override;
  virtual void setExtendedDescriptor(bool extendedDescriptor) override;
  virtual void setRotatedFeatures(bool rotatedFeatures) override;

// Feature interface

public:

  virtual void reset() override;

private:

  double mHessianThreshold;
  int mOctaves;
  int mOctaveLayers;
  bool mExtendedDescriptor;
  bool mRotatedFeatures;
};


/*----------------------------------------------------------------*/


class FME_EXPORT SurfDetectorDescriptor
  : public SurfProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  SurfDetectorDescriptor();
  SurfDetectorDescriptor(double hessianThreshold,
                         int octaves,
                         int octaveLayers,
                         bool extendedDescriptor,
                         bool rotatedFeatures);

  ~SurfDetectorDescriptor() override;

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img, cv::InputArray &mask) override;

// DescriptorExtractor interface

public:

  cv::Mat extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints) override;

// ISurf interface

public:

  void setHessianThreshold(double hessianThreshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setExtendedDescriptor(bool extendedDescriptor) override;
  void setRotatedFeatures(bool rotatedFeatures) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::SURF> mSurf;
};

} // namespace fme

#endif // FME_SURF_DETECTOR_DESCRIPTOR_H
