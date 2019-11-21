#ifndef PHOTOMATCH_LCE_BSESCS_PREPROCESS_H
#define PHOTOMATCH_LCE_BSESCS_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT LceBsescsProperties
  : public ILceBsescs
{

public:

  LceBsescsProperties();
  ~LceBsescsProperties() override;

// ILceBsescs interface

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


class PHOTOMATCH_EXPORT LceBsescsPreprocess
  : public LceBsescsProperties,
    public ImageProcess
{

public:

  LceBsescsPreprocess();
  LceBsescsPreprocess(const QSize &blockSize);
  ~LceBsescsPreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_LCE_BSESCS_PREPROCESS_H
