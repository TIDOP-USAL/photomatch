#ifndef PHOTOMATCH_CLAHE_PREPROCESS_H
#define PHOTOMATCH_CLAHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


/*!
 * \brief CLAHE image preprocess class
 */
class PHOTOMATCH_EXPORT ClaheProperties
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


class PHOTOMATCH_EXPORT ClahePreprocess
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

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

protected:

  cv::Ptr<cv::CLAHE> mCvClahe;

};

} // namespace photomatch

#endif // PHOTOMATCH_CLAHE_PREPROCESS_H
