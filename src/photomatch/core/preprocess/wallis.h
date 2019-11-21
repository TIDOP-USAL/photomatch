#ifndef PHOTOMATCH_WALLIS_PREPROCESS_H
#define PHOTOMATCH_WALLIS_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT WallisProperties
  : public IWallis
{

public:

  WallisProperties();
  ~WallisProperties() override;

// IWallis interface

public:

  virtual double contrast() const override;
  virtual void setContrast(double contrast) override;
  virtual double brightness() const override;
  virtual void setBrightness(double brightness) override;
  virtual int imposedAverage() const override;
  virtual void setImposedAverage(int imposedAverage) override;
  virtual int imposedLocalStdDev() const override;
  virtual void setImposedLocalStdDev(int imposedLocalStdDev) override;
  virtual int kernelSize() const override;
  virtual void setKernelSize(int kernelSize) override;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  double mContrast;
  double mBrightness;
  int mImposedAverage;
  int mImposedLocalStdDev;
  int mKernelSize;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT WallisPreprocess
  : public WallisProperties,
    public ImageProcess
{

public:

  WallisPreprocess();
  WallisPreprocess(double contrast,
                   double brightness,
                   int imposedAverage,
                   int imposedLocalStdDev,
                   int kernelSize);
  ~WallisPreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_WALLIS_PREPROCESS_H
