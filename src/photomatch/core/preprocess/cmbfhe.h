#ifndef PHOTOMATCH_CMBFHE_PREPROCESS_H
#define PHOTOMATCH_CMBFHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


/*!
 * \brief CMBFHE image preprocess class
 */
class PHOTOMATCH_EXPORT CmbfheProperties
  : public ICmbfhe
{
public:
  CmbfheProperties();
  ~CmbfheProperties() override {}

// ICmbfheProperties interface

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


class PHOTOMATCH_EXPORT CmbfhePreprocess
  : public CmbfheProperties,
    public ImageProcess
{

public:

  CmbfhePreprocess();
  CmbfhePreprocess(const QSize &blockSize);
  ~CmbfhePreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_CMBFHE_PREPROCESS_H
