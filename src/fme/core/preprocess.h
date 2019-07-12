#ifndef FME_PREPROCESS_H
#define FME_PREPROCESS_H

#include "fme/fme_global.h"

#include <QSize>

namespace fme
{


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




} // namespace fme

#endif // FME_PREPROCESS_H
