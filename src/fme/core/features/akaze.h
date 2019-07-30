#ifndef FME_AKAZE_DETECTOR_DESCRIPTOR_H
#define FME_AKAZE_DETECTOR_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{


/*!
 * \brief AKAZE detector/descriptor properties class
 */
class FME_EXPORT AkazeProperties
  : public IAkaze
{

public:

  AkazeProperties();
  ~AkazeProperties() override;

// IAkaze interface

public:

  virtual QString descriptorType() const override;
  virtual int descriptorSize() const override;
  virtual int descriptorChannels() const override;
  virtual double threshold() const override;
  virtual int octaves() const override;
  virtual int octaveLayers() const override;
  virtual QString diffusivity() const override;
  virtual void setDescriptorType(const QString &descriptorType) override;
  virtual void setDescriptorSize(int descriptorSize) override;
  virtual void setDescriptorChannels(int channels) override;
  virtual void setThreshold(double threshold) override;
  virtual void setOctaves(int octaves) override;
  virtual void setOctaveLayers(int octaveLayers) override;
  virtual void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  virtual void reset() override;

private:

  QString mDescriptorType;
  int mDescriptorSize;
  int mDescriptorChannels;
  double mThreshold;
  int mOctaves;
  int mOctaveLayers;
  QString mDiffusivity;

};


/*----------------------------------------------------------------*/


class FME_EXPORT AkazeDetectorDescriptor
  : public AkazeProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  AkazeDetectorDescriptor();
  AkazeDetectorDescriptor(const QString &descriptorType,
                          int descriptorSize,
                          int descriptorChannels,
                          double threshold,
                          int octaves,
                          int octaveLayers,
                          QString diffusivity);

  ~AkazeDetectorDescriptor() override;

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img, cv::InputArray &mask) override;

// DescriptorExtractor interface

public:

  cv::Mat extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints) override;


// IAkaze interface

public:

  void setDescriptorType(const QString &descriptorType) override;
  void setDescriptorSize(int descriptorSize) override;
  void setDescriptorChannels(int channels) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::AKAZE> mAkaze;

};

} // namespace fme

#endif // FME_AKAZE_DETECTOR_DESCRIPTOR_H
