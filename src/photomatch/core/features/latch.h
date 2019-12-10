#ifndef PHOTOMATCH_LATCH_DESCRIPTOR_H
#define PHOTOMATCH_LATCH_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{



class PHOTOMATCH_EXPORT LatchProperties
  : public ILatch
{
public:

  LatchProperties();
  LatchProperties(const LatchProperties &latchProperties);
  ~LatchProperties() override;

// ILatch interface

public:

  virtual QString bytes() const override;
  virtual bool rotationInvariance() const override;
  virtual int halfSsdSize() const override;
  virtual void setBytes(const QString &bytes) override;
  virtual void setRotationInvariance(bool rotationInvariance) override;
  virtual void setHalfSsdSize(int halfSsdSize) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  QString mBytes;
  bool mRotationInvariance;
  int mHalfSsdSize;
};

/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT LatchDescriptor
    : public LatchProperties,
      public DescriptorExtractor
{

public:

  LatchDescriptor();
  LatchDescriptor(const LatchDescriptor &latchDescriptor);
  LatchDescriptor(QString bytes,
                  bool rotationInvariance,
                  int halfSsdSize);

  ~LatchDescriptor() override;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;


// IBrief interface

public:

  void setBytes(const QString &bytes) override;
  void setRotationInvariance(bool rotationInvariance) override;
  void setHalfSsdSize(int halfSsdSize) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::LATCH> mLATCH;
};



} // namespace photomatch

#endif // PHOTOMATCH_LATCH_DESCRIPTOR_H
