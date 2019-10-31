#ifndef LIBPHOTOMATCH_GLOBAL_H
#define LIBPHOTOMATCH_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef QT_PROJECT
#include "config_photomatch.h"
#endif

#if defined(PHOTOMATCH_EXPORTS)
#  define PHOTOMATCH_EXPORT Q_DECL_EXPORT
#else
#  define PHOTOMATCH_EXPORT
#endif

#if __cplusplus >= 201103L
#  define PHOTOMATCH_NOEXCEPT noexcept
#  define PHOTOMATCH_NOEXCEPT_OP(x) noexcept((x))
#else
#  define PHOTOMATCH_NOEXCEPT throw ()
#  define PHOTOMATCH_NOEXCEPT_OP(x)
#endif

#endif // LIBPHOTOMATCH_GLOBAL_H
