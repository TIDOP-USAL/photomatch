#ifndef PHOTOMATCH_PREPROCESS_H
#define PHOTOMATCH_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include <QSize>
#include <QObject>

#include <opencv2/features2d.hpp>

#include <tidop/core/flags.h>

namespace photomatch
{

/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT Preprocess
{

public:

  enum class Type
  {
    downsample,
    acebsf,
    clahe,
    cmbfhe,
    decolor,
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


class PHOTOMATCH_EXPORT ImageProcess
{

public:

  ImageProcess() {}
  virtual ~ImageProcess() = default;

  /*!
   * \brief procesa una imagen
   * \param[in] imgIn Imagen
   * \param[out] imgOut Imagen
   * \return true if error
   */
  virtual bool process(const cv::Mat &imgIn, cv::Mat &imgOut) = 0;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT IDownsample
  : public Preprocess
{

public:

  IDownsample() : Preprocess(Preprocess::Type::downsample) {}
  virtual ~IDownsample() = default;

  virtual int maxImageSize() const = 0;
  virtual void setMaxImageSize(int size) = 0;

};


/*----------------------------------------------------------------*/

/*!
 * \brief Interface for ACEBSF (Adaptive contrast enhancement based on modified sigmoid function)
 * S. Lal and M. Chandra, "Efficient algorithm for contrast enhancement of
 * natural images," The International Arab Journal of Information Technology,
 * vol. 11, no. 1, January 2014.
 */
class PHOTOMATCH_EXPORT IAcebsf
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
class PHOTOMATCH_EXPORT IClahe
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
class PHOTOMATCH_EXPORT ICmbfhe
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
 * M. Abdullah-Al-Wadud, Md. Hasanul Kabir, M. Ali Akber Dewan, and O. Chae,
 * "A dynamic histogram equalization for image contrast enhancement,"
 * Intl. Conf. Consumer Electronics, pp. 1-2, 2007.
 * dynamic histogram equalization (DHE)
 */
class PHOTOMATCH_EXPORT IDhe
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
 * \brief The IDecolor class
 * Cewu Lu, Li Xu, Jiaya Jia, “Contrast Preserving Decolorization”,
 * IEEE International Conference on Computational Photography (ICCP), 2012.
 */
class PHOTOMATCH_EXPORT IDecolor
  : public Preprocess
{

public:

  IDecolor() : Preprocess(Preprocess::Type::decolor) {}
  virtual ~IDecolor() = default;

};


/*----------------------------------------------------------------*/


/*!
 * \brief Interface for FAHE class
 * Z. Wang and J. Tao, "A fast implementation of adaptive
 * histogram equalization," in Proc. ICSP, 2006.
 */
class PHOTOMATCH_EXPORT IFahe
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

/*!
 * \brief HMCLAHE (Histogram Modified Contrast Limited Adaptive Histogram Equalization)
 * M. Sundaram, K. Ramar, N.Arumugam and G. Prabin, "Histogram based contrasr enhancement
 * for mammogram images," International Conference on Signal Processing, Communication,
 * Computing and Networking Technologies, 2011.
 */
class PHOTOMATCH_EXPORT IHmclahe
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

/*!
 * \brief LCE-BSESCS
 * H. Ibrahim and S. C. Hoo, “Local contrast enhancement utilizing
 * bidirectional switching equalization of separated and clipped subhistograms,”
 * Mathematical Problems in Engineering, vol. 2014, 2014.
 */
class PHOTOMATCH_EXPORT ILceBsescs
  : public Preprocess
{

public:

  ILceBsescs() : Preprocess(Preprocess::Type::lce_bsescs) {}
  virtual ~ILceBsescs() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

};


/*----------------------------------------------------------------*/

/*!
 * \brief MSRCP (MultiScale Retinex with Chromaticity Preservation)
 * Ana Belén Petro, Catalina Sbert, Jean-Michel Morel,
 * "Multiscale Retinex," Image Processing On Line, 2014.
 */
class PHOTOMATCH_EXPORT IMsrcp
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
 * \brief NOSHP (Non-Overlapped Sub-blocks and local Histogram Projection)
 * B. Liu, W. Jin, Y. Chen, C. Liu, and L. Li, "Contrast enhancement
 * using non-overlapped sub-blocks and local histogram projection,"
 * TCE, vol. 57, no. 2, 2011.
 */
class PHOTOMATCH_EXPORT INoshp
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
 * \brief POHE (Parametric-Oriented Histogram Equalization)
 * Y. F. Liu, J. M. Guo, B. S. Lai, and J. D. Lee, "High efficient
 * contrast enhancement using parametric approximation,"
 * in Proc. IEEE ICASSP, pp. 2444-2448, 26-31 May 2013.
 */
class PHOTOMATCH_EXPORT IPohe
  : public Preprocess
{

public:

  IPohe() : Preprocess(Preprocess::Type::pohe) {}
  virtual ~IPohe() {}

  virtual QSize blockSize() const = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;

};


/*----------------------------------------------------------------*/

/*!
 * \brief RSWHE (Recursively Separated and Weighted Histogram Equalization)
 * Mary Kim and Min Gyo Chung, "Recursively Separated and Weighted
 * Histogram Equalization for Brightness Preservation and Contrast
 * Enhancement," 2008.
 */
class PHOTOMATCH_EXPORT IRswhe
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


class PHOTOMATCH_EXPORT IWallis
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


} // namespace photomatch

Q_DECLARE_METATYPE(photomatch::IRswhe::HistogramCut)

#endif // PHOTOMATCH_PREPROCESS_H
