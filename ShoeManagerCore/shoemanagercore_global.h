#ifndef SHOEMANAGERCORE_GLOBAL_H
#define SHOEMANAGERCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHOEMANAGERCORE_LIBRARY)
#  define SHOEMANAGERCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHOEMANAGERCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SHOEMANAGERCORE_GLOBAL_H
