#ifndef _HACSETTINGSGLOBAL_H_
#define _HACSETTINGSGLOBAL_H_

#include <QtCore/QtGlobal>

#if defined(BUILD_HACSETTINGS)
	#define HACSETTINGS_EXPORT Q_DECL_EXPORT
#else
	#define HACSETTINGS_EXPORT Q_DECL_IMPORT
#endif

#endif // _HACSETTINGSGLOBAL_H_