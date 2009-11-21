#ifndef REDE_GLOBAL_H
#define REDE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(REDE_LIBRARY)
#  define REDESHARED_EXPORT Q_DECL_EXPORT
#else
#  define REDESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // REDE_GLOBAL_H
