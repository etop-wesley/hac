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

CONFIG(host) {
DEFINES += BUILD_HOST
} else {
}

# external depenties
INCLUDEPATH +=
LIBS+=


CONFIG(host) {
DEFINES += BUILD_HOST
INCLUDEPATH +=  ../hac-widgets/widgets/src \
LIBS += -L../hac-widgets/widgets/_build -lhacwidgets
} else {
INCLUDEPATH +=  ${TOOLCHAIN_USR_INSTALL}/include \
                ${TOOLCHAIN_USR_INSTALL}/include/hacwidgets
LIBS += -L/${TOOLCHAIN_USR_INSTALL}/lib -lhacwidgets
}


include(src/src.pri)
include(form/form.pri)
include(res/res.pri)
include(ts/ts.pri)



# install

CONFIG(host) {

HOST_INSTALL = ../hac/Hac
host.path = $$HOST_INSTALL
host.files = $$DESTDIR/*
unix:host.extra = cp -afv  $$DESTDIR/* $${HOST_INSTALL}

INSTALLS += host

} else {

rootfs.path = /${ROOTFS_INSTALL}/usr/lib
rootfs.files = $$DESTDIR/*
unix:rootfs.extra = cp -afv  $$DESTDIR/* ${ROOTFS_INSTALL}/usr/lib

toolchain_include.path = /${TOOLCHAIN_USR_INSTALL}/include/hacsettings
toolchain_include.files = $$HEADERS
unix:toolchain_include.extra = cp -afv   $$HEADERS ${TOOLCHAIN_USR_INSTALL}/include/hacsettings
				
toolchain_lib.path = /${TOOLCHAIN_USR_INSTALL}/lib
toolchain_lib.files = $$DESTDIR/*
unix:toolchain_lib.extra = cp -afv  $$DESTDIR/* ${TOOLCHAIN_USR_INSTALL}/lib

INSTALLS += rootfs toolchain_include toolchain_lib

}
