#ifndef PHOTOMATCH_MSRCP_PREPROCESS_H
#define PHOTOMATCH_MSRCP_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT MsrcpProperties
  : public IMsrcp
{

public:

  MsrcpProperties();
  ~MsrcpProperties() override;

// IMsrcp interface

public:

  virtual double smallScale() const override;
  virtual void setSmallScale(double smallScale) override;
  virtual double midScale() const override;
  virtual void setMidScale(double midScale) override;
  virtual double largeScale() const override;
  virtual void setLargeScale(double largeScale) override;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  double mSmallScale;
  double mMidScale;
  double mLargeScale;
};



/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT MsrcpPreprocess
  : public MsrcpProperties,
    public ImageProcess
{

public:

  MsrcpPreprocess();
  MsrcpPreprocess(double smallScale, double midScale, double largeScale);
  ~MsrcpPreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_MSRCP_PREPROCESS_H
