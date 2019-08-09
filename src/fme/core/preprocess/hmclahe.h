#ifndef FME_HMCLAHE_PREPROCESS_H
#define FME_HMCLAHE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT HmclaheProperties
  : public IHmclahe
{

public:

  HmclaheProperties();
  ~HmclaheProperties() override;

// IHmclaheProperties interface

public:

  virtual QSize blockSize() const override;
  virtual void setBlockSize(const QSize &blockSize) override;
  virtual double l() const override;
  virtual void setL(double l) override;
  virtual double phi() const override;
  virtual void setPhi(double phi) override;

// Preprocess interface

public:

  virtual void reset() override;

private:

  QSize mBlockSize;
  double mL;
  double mPhi;
};



/*----------------------------------------------------------------*/


class FME_EXPORT HmclahePreprocess
  : public HmclaheProperties,
    public ImageProcess
{

public:

  HmclahePreprocess();
  HmclahePreprocess(const QSize &blockSize, double l, double phi);
  ~HmclahePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IHmclahe interface

public:

  void setBlockSize(const QSize &blockSize) override;
  void setL(double l) override;
  void setPhi(double phi) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_HMCLAHE_PREPROCESS_H
