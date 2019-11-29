#ifndef PHOTOMATCH_VGG_DESCRIPTOR_H
#define PHOTOMATCH_VGG_DESCRIPTOR_H


#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

#include <opencv2/xfeatures2d.hpp>


namespace photomatch
{

class VggProperties
  : public IVgg
{

public:

  VggProperties();
  virtual ~VggProperties() override;

// IVgg interface

public:

  virtual QString descriptorType() const override;
  virtual void setDescriptorType(const QString &descriptorType) override;
  virtual double scaleFactor() const override;
  virtual void setScaleFactor(double scaleFactor) override;
  virtual double sigma() const override;
  virtual void setSigma(double sigma) override;
  virtual bool useNormalizeDescriptor() const override;
  virtual void setUseNormalizeDescriptor(bool useNormalizeDescriptor) override;
  virtual bool useNormalizeImage() const override;
  virtual void setUseNormalizeImage(bool useNormalizeImage) override;
  virtual bool useScaleOrientation() const override;
  virtual void setUseScaleOrientation(bool useScaleOrientation) override;

// Feature interface

public:

  void reset() override;
  QString name() const override;

private:

  QString mDescriptorType;
  double mScaleFactor;
  double mSigma;
  bool bUseNormalizeDescriptor;
  bool bUseNormalizeImage;
  bool bUseScaleOrientation;

};



/*----------------------------------------------------------------*/


class VggDescriptor
  : public VggProperties,
    public DescriptorExtractor
{

public:

  VggDescriptor();
  VggDescriptor(QString descriptorType,
                double scaleFactor,
                double sigma,
                bool useNormalizeDescriptor,
                bool useNormalizeImage,
                bool useScaleOrientation);
  ~VggDescriptor() override;

private:

  void update();

// Feature interface

public:

  void reset() override;

// IVgg interface

public:

  void setDescriptorType(const QString &descriptorType) override;
  void setScaleFactor(double scaleFactor) override;
  void setSigma(double sigma) override;
  void setUseNormalizeDescriptor(bool useNormalizeDescriptor) override;
  void setUseNormalizeImage(bool useNormalizeImage) override;
  void setUseScaleOrientation(bool useScaleOrientation) override;

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints, cv::Mat &descriptors) override;

protected:

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  cv::Ptr<cv::xfeatures2d::VGG> mVGG;
#endif
};


} // namespace photomatch

#endif // PHOTOMATCH_VGG_DESCRIPTOR_H
