#ifndef FME_LATCH_DESCRIPTOR_H
#define FME_LATCH_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace fme
{



class FME_EXPORT LatchProperties
  : public ILatch
{
public:

  LatchProperties();
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


class FME_EXPORT LatchDescriptor
    : public LatchProperties,
      public DescriptorExtractor
{

public:

  LatchDescriptor();
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



} // namespace fme

#endif // FME_LATCH_DESCRIPTOR_H
