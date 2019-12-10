#ifndef PHOTOMATCH_CLAHE_PREPROCESS_H
#define PHOTOMATCH_CLAHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>
#ifdef HAVE_CUDA
#include <opencv2/cudaimgproc.hpp>
#endif // HAVE_CUDA

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
  ClaheProperties(const ClaheProperties &claheProperties);
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
  ClahePreprocess(const ClahePreprocess &clahePreprocess);
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

/*----------------------------------------------------------------*/

#ifdef HAVE_CUDA

class PHOTOMATCH_EXPORT ClahePreprocessCuda
  : public ClaheProperties,
    public ImageProcess
{

public:

  ClahePreprocessCuda();
  ClahePreprocessCuda(const ClahePreprocessCuda &clahePreprocessCuda);
  ClahePreprocessCuda(double clipLimit, const QSize &tilesGridSize);
  ~ClahePreprocessCuda() override;

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

  cv::Ptr<cv::cuda::CLAHE> mCvClahe;

};

#endif // HAVE_CUDA

} // namespace photomatch

#endif // PHOTOMATCH_CLAHE_PREPROCESS_H
