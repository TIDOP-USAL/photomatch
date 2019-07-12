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


} // namespace fme

#endif // FME_PREPROCESS_H
