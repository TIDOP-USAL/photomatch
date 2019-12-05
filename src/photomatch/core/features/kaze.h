#ifndef PHOTOMATCH_KAZE_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_KAZE_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT KazeProperties
  : public IKaze
{
public:

  KazeProperties();
  KazeProperties(const KazeProperties &kazeProperties);
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


class PHOTOMATCH_EXPORT KazeDetectorDescriptor
  : public KazeProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  KazeDetectorDescriptor();
  KazeDetectorDescriptor(const KazeDetectorDescriptor &kazeDetectorDescriptor);
  KazeDetectorDescriptor(bool extendedDescriptor,
                         bool upright,
                         double threshold,
                         int octaves,
                         int octaveLayers,
                         QString diffusivity);

  ~KazeDetectorDescriptor() override;

private:

#if CV_VERSION_MAJOR >= 4
  cv::KAZE::DiffusivityType convertDiffusivity(const QString &diffusivity);
#else
  int convertDiffusivity(const QString &diffusivity);
#endif
  void updateCvKaze();

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

} // namespace photomatch

#endif // PHOTOMATCH_KAZE_DETECTOR_DESCRIPTOR_H
