

#ifndef _ARMSYS2440KEYBOARDHANDLER_H_
#define _ARMSYS2440KEYBOARDHANDLER_H_

#include <qkbd_qws.h> // DO NOT use "qkeyboard_qws.h"! it's a x11 version and will cause segment fault run-time.

typedef struct QWSKeyMap {
    ushort key_code;
    ushort unicode;
    ushort shift_unicode;
    ushort ctrl_unicode;
};

class ArmSys2440KeyboardHandlerPrivate;

class ArmSys2440KeyboardHandler: public QWSKeyboardHandler {
public:
	explicit ArmSys2440KeyboardHandler(const QString &driver = QString(), const QString &device = QString());
	~ArmSys2440KeyboardHandler();

protected:
	friend class ArmSys2440KeyboardHandlerPrivate;
	ArmSys2440KeyboardHandlerPrivate *d;
};

#endif // _MIRKEYBOARDHANDLER_H_
