# #################################################################
# HAC project file
# init create ------------------------------ wesley.xie 2009-10-26
# #################################################################

# configure
TARGET = hac01
TEMPLATE = app
CONFIG += release debug
QT -= network

# directories
DESTDIR = _build
OBJECTS_DIR = _obj
MOC_DIR = _moc
UI_DIR = _ui
RCC_DIR = _rcc


INCLUDEPATH +=	${TOOLCHAIN_USR_INSTALL}/include \
                ${TOOLCHAIN_USR_INSTALL}/include/hacwidgets
	
LIBS += -L/${TOOLCHAIN_USR_INSTALL}/lib -lhacwidgets -lqextserialport

include(src/src.pri)
include(form/form.pri)
include(res/res.pri)
include(ts/ts.pri)

# install
target.path = /${ROOTFS_INSTALL}/usr/bin
INSTALLS += target
