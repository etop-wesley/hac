
THIS_DIR = src/device

INCLUDEPATH += $${THIS_DIR}

SOURCES	+=	$${THIS_DIR}/hacdevice.cpp \
		$${THIS_DIR}/hacdevicemanager.cpp \
		$${THIS_DIR}/hacswitchdevice.cpp

HEADERS +=	$${THIS_DIR}/hacdevice.h \
		$${THIS_DIR}/hacdevicemanager.h \
		$${THIS_DIR}/hacswitchdevice.h
