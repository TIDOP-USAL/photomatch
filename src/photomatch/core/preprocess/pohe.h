#ifndef PHOTOMATCH_POHE_PREPROCESS_H
#define PHOTOMATCH_POHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT PoheProperties
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


class PHOTOMATCH_EXPORT PohePreprocess
  : public PoheProperties,
    public ImageProcess
{

public:

  PohePreprocess();
  PohePreprocess(const QSize &blockSize);
  ~PohePreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_POHE_PREPROCESS_H
