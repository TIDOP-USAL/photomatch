#ifndef FME_CMBFHE_PREPROCESS_H
#define FME_CMBFHE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


/*!
 * \brief CMBFHE image preprocess class
 */
class FME_EXPORT CmbfheProperties
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


class FME_EXPORT CmbfhePreprocess
  : public CmbfheProperties,
    public ImageProcess
{

public:

  CmbfhePreprocess();
  CmbfhePreprocess(const QSize &blockSize);
  ~CmbfhePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// ICmbfhe interface

public:

  void setBlockSize(const QSize &blockSize) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_CMBFHE_PREPROCESS_H
