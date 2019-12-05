#ifndef PHOTOMATCH_GFTT_DETECTOR_H
#define PHOTOMATCH_GFTT_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT GfttProperties
  : public IGftt
{
public:

  GfttProperties();
  GfttProperties(const GfttProperties &gfttProperties);
  ~GfttProperties() override;

// IGftt interface

public:

  virtual int maxFeatures() const override;
  virtual double qualityLevel() const override;
  virtual double minDistance() const override;
  virtual int blockSize() const override;
  virtual bool harrisDetector() const override;
  virtual double k() const override;
  virtual void setMaxFeatures(int maxFeatures) override;
  virtual void setQualityLevel(double qlevel) override;
  virtual void setMinDistance(double minDistance) override;
  virtual void setBlockSize(int blockSize) override;
  virtual void setHarrisDetector(bool value) override;
  virtual void setK(double k) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  int mMaxFeatures;
  double mQualityLevel;
  double mMinDistance;
  int mBlockSize;
  bool mHarrisDetector;
  double mK;

};


/*----------------------------------------------------------------*/


class GfttDetector
  : public GfttProperties,
    public KeypointDetector
{

public:

  GfttDetector();
  GfttDetector(const GfttDetector &gfttDetector);
  GfttDetector(int maxFeatures,
               double qualityLevel,
               double minDistance,
               int blockSize,
               bool harrisDetector,
               double k);
  ~GfttDetector() override;

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask) override;

// IGftt interface

public:

  void setMaxFeatures(int maxFeatures) override;
  void setQualityLevel(double qlevel) override;
  void setMinDistance(double minDistance) override;
  void setBlockSize(int blockSize) override;
  void setHarrisDetector(bool value) override;
  void setK(double k) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::GFTTDetector> mGFTT;

};


} // namespace photomatch

#endif // PHOTOMATCH_GFTT_DETECTOR_H
