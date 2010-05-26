# #################################################################
# HAC project file
# init create ------------------------------ wesley.xie 2009-10-26
# #################################################################

# configure
TARGET = hac01
TEMPLATE = app
CONFIG += release
QT -= network

# directories
DESTDIR = _build
OBJECTS_DIR = _obj
MOC_DIR = _moc
UI_DIR = _ui
RCC_DIR = _rcc

CONFIG(host) {
DEFINES += BUILD_HOST
INCLUDEPATH +=	../hac-widgets/widgets/src

LIBS +=	-L../hac-widgets/widgets/_build
unix: LIBS += -lhacwidgets
win32-g++: LIBS += -lhacwidgets1
} else {

INCLUDEPATH +=	${TOOLCHAIN_USR_INSTALL}/include \
                ${TOOLCHAIN_USR_INSTALL}/include/hacwidgets
	
LIBS += -L/${TOOLCHAIN_USR_INSTALL}/lib -lhacwidgets

}

include(src/src.pri)
include(form/form.pri)
include(res/res.pri)
include(ss/ss.pri)
include(ts/ts.pri)

# install
CONFIG(host) {
target.path = ./Hac
INSTALLS += target
} else {
target.path = /${ROOTFS_INSTALL}/usr/bin
INSTALLS += target
}
