#ifndef PHOTOMATCH_FAHE_PREPROCESS_H
#define PHOTOMATCH_FAHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


/*!
 * \brief Fahe image preprocess class
 */
class PHOTOMATCH_EXPORT FaheProperties
  : public IFahe
{

public:

  FaheProperties();
  FaheProperties(const FaheProperties &faheProperties);
  ~FaheProperties() override = default;

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


class PHOTOMATCH_EXPORT FahePreprocess
  : public FaheProperties,
    public ImageProcess
{

public:

  FahePreprocess();
  FahePreprocess(const FahePreprocess &fahePreprocess);
  FahePreprocess(const QSize &blockSize);
  ~FahePreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_FAHE_PREPROCESS_H
