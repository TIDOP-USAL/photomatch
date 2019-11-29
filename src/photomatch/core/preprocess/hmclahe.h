#ifndef PHOTOMATCH_HMCLAHE_PREPROCESS_H
#define PHOTOMATCH_HMCLAHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT HmclaheProperties
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
  QString name() const final;

private:

  QSize mBlockSize;
  double mL;
  double mPhi;
};



/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT HmclahePreprocess
  : public HmclaheProperties,
    public ImageProcess
{

public:

  HmclahePreprocess();
  HmclahePreprocess(const QSize &blockSize, double l, double phi);
  ~HmclahePreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_HMCLAHE_PREPROCESS_H
