#ifndef FME_MSRCP_PREPROCESS_H
#define FME_MSRCP_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT MsrcpProperties
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


class FME_EXPORT MsrcpPreprocess
  : public MsrcpProperties,
    public ImageProcess
{

public:

  MsrcpPreprocess();
  MsrcpPreprocess(double smallScale, double midScale, double largeScale);
  ~MsrcpPreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IMsrcp interface

public:

  void setSmallScale(double smallScale) override;
  void setMidScale(double midScale) override;
  void setLargeScale(double largeScale) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_MSRCP_PREPROCESS_H
