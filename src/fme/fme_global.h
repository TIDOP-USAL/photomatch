#ifndef LIBFME_GLOBAL_H
#define LIBFME_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef QT_PROJECT
#include "config_fme.h"
#endif

#if defined(FME_EXPORTS)
#  define FME_EXPORT Q_DECL_EXPORT
#else
#  define FME_EXPORT
#endif

#if __cplusplus >= 201103L
#  define FME_NOEXCEPT noexcept
#  define FME_NOEXCEPT_OP(x) noexcept((x))
#else
#  define FME_NOEXCEPT throw ()
#  define FME_NOEXCEPT_OP(x)
#endif

#endif // LIBFME_GLOBAL_H
