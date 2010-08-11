# qmake project file for building the hacwidgets libraries

HW_ROOT = ..

include( $${HW_ROOT}/config.pri )

SUFFIX_STR =
VVERSION = $$[QT_VERSION]
isEmpty(VVERSION) {

    # Qt 3
    debug {
        SUFFIX_STR = $${DEBUG_SUFFIX}
    } else {
        SUFFIX_STR = $${RELEASE_SUFFIX} 
    }
} else {
    CONFIG(debug, debug|release) {
        SUFFIX_STR = $${DEBUG_SUFFIX}
    } else {
        SUFFIX_STR = $${RELEASE_SUFFIX}
    }
}

TARGET            = hacwidgets$${SUFFIX_STR}
TEMPLATE          = lib
QT -= network

MOC_DIR		= _moc
OBJECTS_DIR	= _obj$${SUFFIX_STR}
RCC_DIR		= _rcc
UI_DIR		= _ui
DESTDIR		= _build

contains(CONFIG, Dll) {
    CONFIG += dll
} else {
    CONFIG += staticlib
}

win32:Dll {
    DEFINES    += QT_DLL HACWIDGETS_DLL HACWIDGETS_MAKEDLL
}

include(src/src.pri)
include(form/form.pri)
include(res/res.pri)
include(ts/ts.pri)

# Install

CONFIG(host) {
INSTALLS += target
} else {
rootfs.path = /${ROOTFS_INSTALL}/usr/lib
rootfs.files = $$DESTDIR/*so*
rootfs.extra = cp -afv  $$rootfs.files $$rootfs.path

toolchain_include.path = /${TOOLCHAIN_USR_INSTALL}/include/hacwidgets
toolchain_include.files = $$HEADERS
toolchain_include.extra = cp -afv $$HEADERS ${TOOLCHAIN_USR_INSTALL}/include/hacwidgets
				
toolchain_lib.path = /${TOOLCHAIN_USR_INSTALL}/lib
toolchain_lib.files = $$DESTDIR/*so*
toolchain_lib.extra = cp -afv $$toolchain_lib.files $$toolchain_lib.path

INSTALLS += rootfs toolchain_include toolchain_lib
}
