#ifndef FME_KAZE_DETECTOR_DESCRIPTOR_H
#define FME_KAZE_DETECTOR_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{


class FME_EXPORT KazeProperties
  : public IKaze
{
public:

  KazeProperties();
  ~KazeProperties() override;

// IKaze interface

public:

  virtual bool extendedDescriptor() const override;
  virtual bool upright() const override;
  virtual double threshold() const override;
  virtual int octaves() const override;
  virtual int octaveLayers() const override;
  virtual QString diffusivity() const override;
  virtual void setExtendedDescriptor(bool extended) override;
  virtual void setUpright(bool upright) override;
  virtual void setThreshold(double threshold) override;
  virtual void setOctaves(int octaves) override;
  virtual void setOctaveLayers(int octaveLayers) override;
  virtual void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  bool mExtended;
  bool mUpright;
  double mThreshold;
  int mOctaves;
  int mOctaveLayers;
  QString mDiffusivity;

};


/*----------------------------------------------------------------*/


class FME_EXPORT KazeDetectorDescriptor
  : public KazeProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  KazeDetectorDescriptor();
  KazeDetectorDescriptor(bool extendedDescriptor,
                         bool upright,
                         double threshold,
                         int octaves,
                         int octaveLayers,
                         QString diffusivity);

  ~KazeDetectorDescriptor() override;

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

// IKaze interface

public:

  void setExtendedDescriptor(bool extended) override;
  void setUpright(bool upright) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::KAZE> mKaze;
};

} // namespace fme

#endif // FME_KAZE_DETECTOR_DESCRIPTOR_H
