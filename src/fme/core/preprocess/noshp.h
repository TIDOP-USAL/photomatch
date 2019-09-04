#ifndef FME_NOSHP_PREPROCESS_H
#define FME_NOSHP_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT NoshpProperties
  : public INoshp
{

public:

  NoshpProperties();
  ~NoshpProperties() override;

// INoshp interface

public:

  virtual QSize blockSize() const override;
  virtual void setBlockSize(const QSize &blockSize) override;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  QSize mBlockSize;

};



/*----------------------------------------------------------------*/


class FME_EXPORT NoshpPreprocess
  : public NoshpProperties,
    public ImageProcess
{

public:

  NoshpPreprocess();
  NoshpPreprocess(const QSize &blockSize);
  ~NoshpPreprocess() override;

// Preprocess interface

public:

  void reset() override;

// INoshp interface

public:

  void setBlockSize(const QSize &blockSize) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_NOSHP_PREPROCESS_H
