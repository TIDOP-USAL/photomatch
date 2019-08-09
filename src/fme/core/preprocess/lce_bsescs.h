#ifndef FME_LCE_BSESCS_PREPROCESS_H
#define FME_LCE_BSESCS_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT LceBsescsProperties
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

private:

  QSize mBlockSize;
};



/*----------------------------------------------------------------*/


class FME_EXPORT LceBsescsPreprocess
  : public LceBsescsProperties,
    public ImageProcess
{

public:

  LceBsescsPreprocess();
  LceBsescsPreprocess(const QSize &blockSize);
  ~LceBsescsPreprocess() override;

// Preprocess interface

public:

  void reset() override;

// ILceBsescs interface

public:

  void setBlockSize(const QSize &blockSize) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_LCE_BSESCS_PREPROCESS_H
