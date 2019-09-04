#ifndef FME_LUCID_DESCRIPTOR_H
#define FME_LUCID_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT LucidProperties
  : public ILucid
{
public:

  LucidProperties();
  ~LucidProperties() override;

// ILucid interface

public:

  virtual int lucidKernel() const override;
  virtual int blurKernel() const override;
  virtual void setLucidKernel(int lucidKernel) override;
  virtual void setBlurKernel(int blurKernel) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  int mLucidKernel;
  int mBlurKernel;
};


/*----------------------------------------------------------------*/


class FME_EXPORT LucidDescriptor
    : public LucidProperties,
      public DescriptorExtractor
{

public:

  LucidDescriptor();
  LucidDescriptor(int lucidKernel, int blurKernel);

  ~LucidDescriptor() override;

private:

  void update();

// DescriptorExtractor interface

public:

  cv::Mat extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints) override;


// ILucid interface

public:

  void setLucidKernel(int lucidKernel) override;
  void setBlurKernel(int blurKernel) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::LUCID> mLUCID;
};


/*----------------------------------------------------------------*/


} // namespace fme

#endif // FME_LUCID_DESCRIPTOR_H
