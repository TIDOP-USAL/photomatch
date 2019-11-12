#ifndef PHOTOMATCH_BOOST_DESCRIPTOR_H
#define PHOTOMATCH_BOOST_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

#include <opencv2/xfeatures2d.hpp>
#ifdef HAVE_CUDA
#include <opencv2/cudafeatures2d.hpp>
#include "opencv2/xfeatures2d/cuda.hpp"
#endif // HAVE_CUDA

namespace photomatch
{

class BoostProperties
  : public IBoost
{

public:

  BoostProperties();
  ~BoostProperties() override;

// IBoost interface

public:

  virtual QString descriptorType() const override;
  virtual bool useOrientation() const override;
  virtual double scaleFactor() const override;
  virtual void setDescriptorType(const QString &descriptorType) override;
  virtual void setUseOrientation(bool useOrientation) override;
  virtual void setScaleFactor(double scaleFactor) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const override;

private:

  QString mDescriptorType;
  bool bUseOrientation;
  double mScaleFactor;

};


/*----------------------------------------------------------------*/

class BoostDescriptor
  : public BoostProperties,
    public DescriptorExtractor
{

public:

  BoostDescriptor();
  BoostDescriptor(QString descriptorType,
                  bool useOrientation,
                  double scaleFactor);
  ~BoostDescriptor() override;

private:

  void update();

// Feature interface

public:

  void reset() override;

// IBoost interface

public:

  void setDescriptorType(const QString &descriptorType) override;
  void setUseOrientation(bool useOrientation) override;
  void setScaleFactor(double scaleFactor) override;

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints, cv::Mat &descriptors) override;

protected:

#if CV_VERSION_MAJOR >= 3
#  if CV_VERSION_MINOR > 2
  cv::Ptr<cv::xfeatures2d::BoostDesc> mBoost;
#  endif
#endif

};



} // namespace photomatch

#endif // PHOTOMATCH_BOOST_DESCRIPTOR_H
