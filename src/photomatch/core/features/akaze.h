#ifndef PHOTOMATCH_AKAZE_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_AKAZE_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


/*!
 * \brief AKAZE detector/descriptor properties class
 */
class PHOTOMATCH_EXPORT AkazeProperties
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
  QString name() const final;

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


class PHOTOMATCH_EXPORT AkazeDetectorDescriptor
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

} // namespace photomatch

#endif // PHOTOMATCH_AKAZE_DETECTOR_DESCRIPTOR_H
