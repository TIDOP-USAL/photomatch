#ifndef LIBFME_GLOBAL_H
#define LIBFME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FME_EXPORTS)
#  define FME_EXPORT Q_DECL_EXPORT
#else
#  define FME_EXPORT
#endif

#endif // LIBFME_GLOBAL_H
