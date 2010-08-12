# configure
TEMPLATE = lib
TARGET = hacsettings
CONFIG += release
DEFINES += BUILD_HACSETTINGS

# temporary directories
DESTDIR = _build
OBJECTS_DIR = _obj
MOC_DIR = _moc
UI_DIR = _ui
RCC_DIR = _rcc

# external depenties
INCLUDEPATH +=  ${TOOLCHAIN_USR_INSTALL}/include \
                ${TOOLCHAIN_USR_INSTALL}/include/hacwidgets
LIBS += -L/${TOOLCHAIN_USR_INSTALL}/lib -lhacwidgets

# sub directories
include(src/src.pri)
include(form/form.pri)
include(res/res.pri)
include(ts/ts.pri)

# install
toolchain_include.path = /${TOOLCHAIN_USR_INSTALL}/include/hacsettings
toolchain_include.files = $$HEADERS
unix:toolchain_include.extra = cp -afv $$toolchain_include.files $$toolchain_include.path
				
toolchain_lib.path = /${TOOLCHAIN_USR_INSTALL}/lib
toolchain_lib.files = $$DESTDIR/*
unix:toolchain_lib.extra = cp -afv $$toolchain_lib.files $$toolchain_include.path

rootfs.path = /${ROOTFS_INSTALL}/usr/lib
rootfs.files = $$DESTDIR/*
unix:rootfs.extra = cp -afv  $$rootfs.files $$rootfs.path

INSTALLS += toolchain_include toolchain_lib rootfs
