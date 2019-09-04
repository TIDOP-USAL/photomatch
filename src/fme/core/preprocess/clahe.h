#ifndef FME_CLAHE_PREPROCESS_H
#define FME_CLAHE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


/*!
 * \brief CLAHE image preprocess class
 */
class FME_EXPORT ClaheProperties
  : public IClahe
{

public:

  ClaheProperties();
  ~ClaheProperties() override = default;

// IClahe interface

public:

  virtual double clipLimit() const override;
  virtual void setClipLimit(double clipLimit) override;
  virtual QSize tilesGridSize() const override;
  virtual void setTilesGridSize(const QSize &tilesGridSize) override;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  double mClipLimit;
  QSize mTilesGridSize;
};


/*----------------------------------------------------------------*/


class FME_EXPORT ClahePreprocess
  : public ClaheProperties,
    public ImageProcess
{

public:

  ClahePreprocess();
  ClahePreprocess(double clipLimit, const QSize &tilesGridSize);
  ~ClahePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IClahe interface

public:

  void setClipLimit(double clipLimit) override;
  void setTilesGridSize(const QSize &tilesGridSize) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

protected:

  cv::Ptr<cv::CLAHE> mCvClahe;

};

} // namespace fme

#endif // FME_CLAHE_PREPROCESS_H
