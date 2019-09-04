#ifndef FME_PREPROCESS_H
#define FME_PREPROCESS_H

#include "fme/fme_global.h"

#include <QSize>
#include <QObject>

#include <opencv2/features2d.hpp>

#include <tidop/core/flags.h>

namespace fme
{

/*----------------------------------------------------------------*/


class FME_EXPORT Preprocess
{

public:

  enum class Type
  {
    downsample,
    acebsf,
    clahe,
    cmbfhe,
    dhe,
    fahe,
    hmclahe,
    lce_bsescs,
    msrcp,
    noshp,
    pohe,
    rswhe,
    wallis
  };

public:

  Preprocess(Type type) : mPreprocessType(type) {}
  virtual ~Preprocess() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  Type type() const { return mPreprocessType.flags(); }
  virtual QString name() const = 0;

protected:

  tl::EnumFlags<Type> mPreprocessType;

};
ALLOW_BITWISE_FLAG_OPERATIONS(Preprocess::Type)

/*----------------------------------------------------------------*/


class FME_EXPORT ImageProcess
{

public:

  ImageProcess() {}
  virtual ~ImageProcess() = default;

  /*!
   * \brief procesa una imagen
   * \param[in] img Imagen
   * \return Descriptores
   */
  virtual cv::Mat process(const cv::Mat &img) = 0;

};


/*----------------------------------------------------------------*/


class FME_EXPORT IDownsample
  : public Preprocess
{

public:

  IDownsample() : Preprocess(Preprocess::Type::downsample) {}
  virtual ~IDownsample() = default;

  virtual int maxImageSize() const = 0;
  virtual void setMaxImageSize(int size) = 0;

};


/*----------------------------------------------------------------*/


class FME_EXPORT IAcebsf
  : public Preprocess
{

public:

  IAcebsf() : Preprocess(Preprocess::Type::acebsf) {}
  virtual ~IAcebsf() = default;

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual double l() const = 0;
  virtual void setL(double l) = 0;
  virtual double k1() const  = 0;
  virtual void setK1(double k1) = 0;
  virtual double k2() const = 0;
  virtual void setK2(double k2) = 0;

};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for CLAHE (Contrast Limited Adaptive Histogram Equalization)
 * Equalizes the histogram of a grayscale image using Contrast Limited
 * Adaptive Histogram Equalization.
 */
class FME_EXPORT IClahe
  : public Preprocess
{

public:

  IClahe() : Preprocess(Preprocess::Type::clahe) {}
  virtual ~IClahe() = default;

  virtual double clipLimit() const = 0;
  virtual void setClipLimit(double clipLimit) = 0;
  virtual QSize tilesGridSize() const = 0;
  virtual void setTilesGridSize (const QSize &tilesGridSize) = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for CMBFHE class
 * F. Lamberti, B. Montrucchio, and A. Sanna, "CMBFHE: a novel contrast
 * enhancement technique based on cascaded multistep binomial filtering
 * histogram equalization," TCE, vol. 52, no. 3, 2006.
 */
class FME_EXPORT ICmbfhe
  : public Preprocess
{

public:

  ICmbfhe() : Preprocess(Preprocess::Type::cmbfhe) {}
  virtual ~ICmbfhe() = default;

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;
};


/*----------------------------------------------------------------*/

/*!
 * \brief The IDhe class
 * dynamic histogram equalization (DHE)
 */
class FME_EXPORT IDhe
  : public Preprocess
{

public:

  IDhe() : Preprocess(Preprocess::Type::dhe) {}
  virtual ~IDhe() = default;

  virtual int x() const = 0;
  virtual void setX(int x) = 0;

};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for FAHE class
 * Z. Wang and J. Tao, "A fast implementation of adaptive
 * histogram equalization," in Proc. ICSP, 2006.
 */
class FME_EXPORT IFahe
  : public Preprocess
{

public:

  IFahe() : Preprocess(Preprocess::Type::fahe) {}
  virtual ~IFahe() = default;

  ///TODO: las dimensiones tienen que ser iguales
  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

};


/*----------------------------------------------------------------*/


class FME_EXPORT IHmclahe
  : public Preprocess
{

public:

  IHmclahe() : Preprocess(Preprocess::Type::hmclahe) {}
  virtual ~IHmclahe() = default;

  ///TODO: las dimensiones tienen que ser iguales
  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual double l() const = 0;
  virtual void setL(double l) = 0;
  virtual double phi() const  = 0;
  virtual void setPhi(double phi) = 0;
};


/*----------------------------------------------------------------*/


class FME_EXPORT ILceBsescs
  : public Preprocess
{

public:

  ILceBsescs() : Preprocess(Preprocess::Type::lce_bsescs) {}
  virtual ~ILceBsescs() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

};


/*----------------------------------------------------------------*/


class FME_EXPORT IMsrcp
  : public Preprocess
{

public:

  IMsrcp() : Preprocess(Preprocess::Type::msrcp) {}
  virtual ~IMsrcp() = default;

  virtual double smallScale() const = 0;
  virtual void setSmallScale(double smallScale) = 0;
  virtual double midScale() const  = 0;
  virtual void setMidScale(double midScale) = 0;
  virtual double largeScale() const = 0;
  virtual void setLargeScale(double largeScale) = 0;

};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for NOSHP class
 */
class FME_EXPORT INoshp
  : public Preprocess
{

public:

  INoshp() : Preprocess(Preprocess::Type::noshp) {}
  virtual ~INoshp() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for POHE class
 * Y. F. Liu, J. M. Guo, B. S. Lai, and J. D. Lee, "High efficient
 * contrast enhancement using parametric approximation,"
 * in Proc. IEEE ICASSP, pp. 2444-2448, 26-31 May 2013.
 */
class FME_EXPORT IPohe
  : public Preprocess
{

public:

  IPohe() : Preprocess(Preprocess::Type::pohe) {}
  virtual ~IPohe() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

};


/*----------------------------------------------------------------*/


class FME_EXPORT IRswhe
  : public Preprocess
{

public:

  enum class HistogramCut{
    by_mean,
    by_median
  };

public:

  IRswhe() : Preprocess(Preprocess::Type::rswhe) {}
  virtual ~IRswhe() = default;

  virtual int histogramDivisions() const = 0;
  virtual void setHistogramDivisions(int histogramDivisions) = 0;
  virtual HistogramCut histogramCut() const = 0;
  virtual void setHistogramCut(HistogramCut histogramCut) = 0;

};

/*----------------------------------------------------------------*/


class FME_EXPORT IWallis
  : public Preprocess
{
public:

  IWallis() : Preprocess(Preprocess::Type::wallis) {}
  virtual ~IWallis() = default;

  virtual double contrast() const = 0;
  virtual void setContrast(double contrast) = 0;
  virtual double brightness() const = 0;
  virtual void setBrightness(double brightness) = 0;
  virtual int imposedAverage() const = 0;
  virtual void setImposedAverage(int imposedAverage) = 0;
  virtual int imposedLocalStdDev() const = 0;
  virtual void setImposedLocalStdDev(int imposedLocalStdDev) = 0;
  virtual int kernelSize() const = 0;
  virtual void setKernelSize(int kernelSize) = 0;

};


} // namespace fme

Q_DECLARE_METATYPE(fme::IRswhe::HistogramCut)

#endif // FME_PREPROCESS_H
