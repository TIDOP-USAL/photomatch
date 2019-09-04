#ifndef FME_POHE_PREPROCESS_H
#define FME_POHE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT PoheProperties
  : public IPohe
{

public:

  PoheProperties();
  ~PoheProperties() override;

// IPohe interface

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


class FME_EXPORT PohePreprocess
  : public PoheProperties,
    public ImageProcess
{

public:

  PohePreprocess();
  PohePreprocess(const QSize &blockSize);
  ~PohePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IPohe interface

public:

  void setBlockSize(const QSize &blockSize) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_POHE_PREPROCESS_H
