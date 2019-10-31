#ifndef PHOTOMATCH_NOSHP_PREPROCESS_H
#define PHOTOMATCH_NOSHP_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT NoshpProperties
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


class PHOTOMATCH_EXPORT NoshpPreprocess
  : public NoshpProperties,
    public ImageProcess
{

public:

  NoshpPreprocess();
  NoshpPreprocess(const QSize &blockSize);
  ~NoshpPreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_NOSHP_PREPROCESS_H
