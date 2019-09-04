#ifndef FME_WALLIS_PREPROCESS_H
#define FME_WALLIS_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT WallisProperties
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


class FME_EXPORT WallisPreprocess
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

// Preprocess interface

public:

  void reset() override;

// IPohe interface

public:

  void setContrast(double contrast) override;
  void setBrightness(double brightness) override;
  void setImposedAverage(int imposedAverage) override;
  void setImposedLocalStdDev(int imposedLocalStdDev) override;
  void setKernelSize(int kernelSize) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_WALLIS_PREPROCESS_H
