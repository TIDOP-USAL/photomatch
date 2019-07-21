#ifndef FME_PREPROCESS_H
#define FME_PREPROCESS_H

#include "fme/fme_global.h"

#include <QSize>

namespace fme
{

/*----------------------------------------------------------------*/

/*!
 * \brief Interface for CLAHE (Contrast Limited Adaptive Histogram Equalization)
 * Equalizes the histogram of a grayscale image using Contrast Limited
 * Adaptive Histogram Equalization.
 */
class FME_EXPORT IClahe
{

public:

  IClahe(){}
  virtual ~IClahe() = default;

  virtual double clipLimit() const = 0;
  virtual void setClipLimit(double clipLimit) = 0;
  virtual QSize tilesGridSize() const = 0;
  virtual void setTilesGridSize (const QSize &tilesGridSize) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for CMBFHE class
 * F. Lamberti, B. Montrucchio, and A. Sanna, "CMBFHE: a novel contrast
 * enhancement technique based on cascaded multistep binomial filtering
 * histogram equalization," TCE, vol. 52, no. 3, 2006.
 */
class FME_EXPORT ICmbfhe
{

public:

  ICmbfhe() {}
  virtual ~ICmbfhe() = default;

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/

/*!
 * \brief The IDhe class
 * dynamic histogram equalization (DHE)
 */
class FME_EXPORT IDhe
{

public:

  IDhe() {}
  virtual ~IDhe() = default;

  virtual int x() const = 0;
  virtual void setX(int x) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for FAHE class
 * Z. Wang and J. Tao, "A fast implementation of adaptive
 * histogram equalization," in Proc. ICSP, 2006.
 */
class FME_EXPORT IFahe
{

public:

  IFahe() {}
  virtual ~IFahe() = default;

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


class FME_EXPORT IHmclahe
{

public:

  IHmclahe(){}
  virtual ~IHmclahe() = default;

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual double l() const = 0;
  virtual void setL(double l) = 0;
  virtual double phi() const  = 0;
  virtual void setPhi(double phi) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


class FME_EXPORT ILceBsescs
{

public:

  ILceBsescs() {}
  virtual ~ILceBsescs() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


class FME_EXPORT IMsrcp
{

public:

  IMsrcp(){}
  virtual ~IMsrcp() = default;

  virtual double smallScale() const = 0;
  virtual void setSmallScale(double smallScale) = 0;
  virtual double midScale() const  = 0;
  virtual void setMidScale(double midScale) = 0;
  virtual double largeScale() const = 0;
  virtual void setLargeScale(double largeScale) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for NOSHP class
 */
class FME_EXPORT INoshp
{

public:

  INoshp() {}
  virtual ~INoshp() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for POHE class
 * Y. F. Liu, J. M. Guo, B. S. Lai, and J. D. Lee, "High efficient
 * contrast enhancement using parametric approximation,"
 * in Proc. IEEE ICASSP, pp. 2444-2448, 26-31 May 2013.
 */
class FME_EXPORT IPohe
{

public:

  IPohe() {}
  virtual ~IPohe() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


class FME_EXPORT IRswhe
{

public:

  enum class HistogramCut{
    by_mean,
    by_median
  };

public:

  IRswhe() {}
  virtual ~IRswhe() = default;

  virtual int histogramDivisions() const = 0;
  virtual void setHistogramDivisions(int histogramDivisions) = 0;
  virtual HistogramCut histogramCut() const = 0;
  virtual void setHistogramCut(HistogramCut histogramCut) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


class FME_EXPORT IWallis
{
public:

  IWallis() {}
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

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};


} // namespace fme

#endif // FME_PREPROCESS_H
