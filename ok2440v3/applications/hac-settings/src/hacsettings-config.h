#ifndef _HACSETTINGSCONFIG_H_
#define _HACSETTINGSCONFIG_H_

#include <QtCore/QtGlobal>

#if defined(BUILD_HACSETTINGS)
	#define HACSETTINGS_EXPORT Q_DECL_EXPORT
#else
	#define HACSETTINGS_EXPORT Q_DECL_IMPORT
#endif

#endif // _HACSETTINGSCONFIG_H_
