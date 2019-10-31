#ifndef PHOTOMATCH_DAISY_DESCRIPTOR_H
#define PHOTOMATCH_DAISY_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{

class PHOTOMATCH_EXPORT DaisyProperties
  : public IDaisy
{
public:

  DaisyProperties();
  ~DaisyProperties() override;

// IDaisy interface

public:

  virtual double radius() const override;
  virtual int qRadius() const override;
  virtual int qTheta() const override;
  virtual int qHist() const override;
  virtual QString norm() const override;
  virtual bool interpolation() const override;
  virtual bool useOrientation() const override;
  virtual void setRadius(double radius) override;
  virtual void setQRadius(int qRadius) override;
  virtual void setQTheta(int qTheta) override;
  virtual void setQHist(int qHist) override;
  virtual void setNorm(const QString &norm) override;
  virtual void setInterpolation(bool interpolation) override;
  virtual void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  double mRadius;
  int mQRadius;
  int mQTheta;
  int mQHist;
  QString mNorm;
  bool mInterpolation;
  bool mUseOrientation;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT DaisyDescriptor
    : public DaisyProperties,
      public DescriptorExtractor
{

public:

  DaisyDescriptor();
  DaisyDescriptor(double radius,
                  int qRadius,
                  int qTheta,
                  int qHist,
                  QString norm,
                  bool interpolation,
                  bool useOrientation);

  ~DaisyDescriptor() override;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;


// IDaisy interface

public:

  void setRadius(double radius) override;
  void setQRadius(int qRadius) override;
  void setQTheta(int qTheta) override;
  void setQHist(int qHist) override;
  void setNorm(const QString &norm) override;
  void setInterpolation(bool interpolation) override;
  void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::DAISY> mDAISY;
};


} // namespace photomatch

#endif // PHOTOMATCH_DAISY_DESCRIPTOR_H
