##############################################

HW_ROOT = ..

include ( $${HW_ROOT}/config.pri )

CONFIG    += warn_on

SUFFIX_STR =

VVERSION = $$[QT_VERSION]
isEmpty(VVERSION) {

    # Qt 3
     debug {
        SUFFIX_STR = $${DEBUG_SUFFIX}
    }
    else {
        SUFFIX_STR = $${RELEASE_SUFFIX}
    }
}
else {

    CONFIG(debug, debug|release) {
        SUFFIX_STR = $${DEBUG_SUFFIX}
    }
    else {
        SUFFIX_STR = $${RELEASE_SUFFIX}
    }
}

TEMPLATE        = lib
MOC_DIR         = _moc
OBJECTS_DIR     = _obj$${SUFFIX_STR}
DESTDIR         = _build
INCLUDEPATH    += $${HW_ROOT}/widgets/src
DEPENDPATH     += $${HW_ROOT}/widgets/src

LIBNAME         = hacwidgets$${SUFFIX_STR}
contains(CONFIG, Dll) {
    win32 {
        DEFINES += QT_DLL HACWIDGETS_DLL
        LIBNAME = $${LIBNAME}$${VER_MAJ}
    }
}

!contains(CONFIG, Widgets) {
    DEFINES += NO_HACWIDGETS_WIDGETS
}

unix:LIBS      += -L$${HW_ROOT}/widgets/_build -l$${LIBNAME}
# unix:LIBS      += -L$${HW_ROOT}/lib -l$${LIBNAME}
win32-msvc:LIBS  += $${HW_ROOT}/lib/$${LIBNAME}.lib
win32-msvc.net:LIBS  += $${HW_ROOT}/lib/$${LIBNAME}.lib
win32-msvc2002:LIBS += $${HW_ROOT}/lib/$${LIBNAME}.lib
win32-msvc2003:LIBS += $${HW_ROOT}/lib/$${LIBNAME}.lib
win32-msvc2005:LIBS += $${HW_ROOT}/lib/$${LIBNAME}.lib
win32-msvc2008:LIBS += $${HW_ROOT}/lib/$${LIBNAME}.lib
#win32-g++:LIBS   += -L$${HW_ROOT}/lib -l$${LIBNAME}
win32-g++:LIBS   += -L$${HW_ROOT}/widgets/_build -l$${LIBNAME}

# isEmpty(QT_VERSION) does not work with Qt-4.1.0/MinGW

VVERSION = $$[QT_VERSION]
isEmpty(VVERSION) {
    # Qt 3 
    TARGET    = hacwidgetsplugin$${SUFFIX_STR}
    CONFIG   += qt plugin

    UI_DIR    = ui

    HEADERS  +=
    SOURCES  +=

    target.path = $(QTDIR)/plugins/designer
    INSTALLS += target

} else {

   # Qt 4

    TARGET    = hacwidgets_designer_plugin$${SUFFIX_STR}
    CONFIG    += qt designer plugin 

    RCC_DIR   = _rcc

    include(src/src.pri)
    include(res/res.pri)

    target.path = $$[QT_INSTALL_PLUGINS]/designer
    INSTALLS += target
}
