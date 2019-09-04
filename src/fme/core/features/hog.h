#ifndef FME_HOG_DESCRIPTOR_H
#define FME_HOG_DESCRIPTOR_H

#include "fme/fme_global.h"

#include <memory>

#include <QString>

#include <opencv2/objdetect.hpp>

#include "fme/core/features/features.h"

namespace fme
{


class FME_EXPORT HogProperties
  : public IHog
{
public:

  HogProperties();
  ~HogProperties() override;

// IHog interface

public:

  virtual QSize winSize() const override;
  virtual QSize blockSize() const override;
  virtual QSize blockStride() const override;
  virtual QSize cellSize() const override;
  virtual int nbins() const override;
  virtual int derivAperture() const override;
  virtual void setWinSize(const QSize &winSize) override;
  virtual void setBlockSize(const QSize &blockSize) override;
  virtual void setBlockStride(const QSize &blockStride) override;
  virtual void setCellSize(const QSize &cellSize) override;
  virtual void setNbins(int nbins) override;
  virtual void setDerivAperture(int derivAperture) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  QSize mWinSize;
  QSize mBlockSize;
  QSize mBlockStride;
  QSize mCellSize;
  int mNbins;
  int mDerivAperture;
};


/*----------------------------------------------------------------*/


class FME_EXPORT HogDescriptor
    : public HogProperties,
      public DescriptorExtractor
{

public:

  HogDescriptor();
  HogDescriptor(QSize winSize,
                QSize blockSize,
                QSize blockStride,
                QSize cellSize,
                int nbins,
                int derivAperture);

  ~HogDescriptor() override;

private:

  void update();
  void normalizepatch(const cv::Mat &gray, const cv::KeyPoint &keypoint, cv::Mat &output);

// DescriptorExtractor interface

public:

  cv::Mat extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints) override;

// IHog interface

public:

  void setWinSize(const QSize &winSize) override;
  void setBlockSize(const QSize &blockSize) override;
  void setBlockStride(const QSize &blockStride) override;
  void setCellSize(const QSize &cellSize) override;
  void setNbins(int nbins) override;
  void setDerivAperture(int derivAperture) override;

// Feature interface

public:

  void reset() override;

protected:

  std::shared_ptr<cv::HOGDescriptor> mHOG;
};


} // namespace fme

#endif // FME_HOG_DESCRIPTOR_H
