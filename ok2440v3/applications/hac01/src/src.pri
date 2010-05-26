
SRC_DIR = src
SRC_GUI_DIR = $${SRC_DIR}/gui
SRC_SETTINGS_DIR = $${SRC_DIR}/settings
SRC_MODEL_DIR = $${SRC_DIR}/model



INCLUDEPATH += $${SRC_DIR} $${SRC_GUI_DIR} $${SRC_MODEL_DIR} $${SRC_SETTINGS_DIR}
LIBS +=

SOURCES += $${SRC_DIR}/main.cpp \
    $${SRC_GUI_DIR}/hacapplication.cpp \
    $${SRC_GUI_DIR}/haccore.cpp \
    $${SRC_GUI_DIR}/hacmainwindow.cpp \
    $${SRC_GUI_DIR}/hacstatuswidget.cpp \
    $${SRC_GUI_DIR}/mainhomepage.cpp \
    $${SRC_GUI_DIR}/mainairconditioningpage.cpp \
    $${SRC_GUI_DIR}/mainlightingpage.cpp \
    $${SRC_GUI_DIR}/mainheatingpage.cpp \
    $${SRC_GUI_DIR}/mainstagepage.cpp \
    $${SRC_GUI_DIR}/mainswitchpage.cpp \
    $${SRC_GUI_DIR}/mainstagemodepage.cpp \
    $${SRC_GUI_DIR}/airconditioningcontrolpage.cpp \
    $${SRC_GUI_DIR}/acscheduleset.cpp \
    $${SRC_GUI_DIR}/lightcontrolpage.cpp \
    $${SRC_GUI_DIR}/switchcontrolpage.cpp \
    $${SRC_GUI_DIR}/heatingcontrolpage.cpp \
    $${SRC_GUI_DIR}/curtainscontrolpage.cpp \
    $${SRC_GUI_DIR}/simulatehomesettings.cpp \
    $${SRC_GUI_DIR}/stagesettingspage.cpp \
    $${SRC_GUI_DIR}/systemmain.cpp \
    $${SRC_SETTINGS_DIR}/regionalsettings.cpp \
    $${SRC_SETTINGS_DIR}/datetimesettings.cpp \
    $${SRC_SETTINGS_DIR}/propertiessettings.cpp \
    $${SRC_SETTINGS_DIR}/calibrationdialog.cpp \
    $${SRC_SETTINGS_DIR}/scribblewidget.cpp


HEADERS += $${SRC_DIR}/hac-config.h \
    $${SRC_GUI_DIR}/armsys2440kbdthread.h \
    $${SRC_GUI_DIR}/hacapplication.h \
    $${SRC_GUI_DIR}/haccore.h \
    $${SRC_GUI_DIR}/hacmainwindow.h \
    $${SRC_GUI_DIR}/hacstatuswidget.h \
    $${SRC_GUI_DIR}/mainhomepage.h \
    $${SRC_GUI_DIR}/mainairconditioningpage.h \
    $${SRC_GUI_DIR}/mainlightingpage.h \
    $${SRC_GUI_DIR}/mainheatingpage.h \
    $${SRC_GUI_DIR}/mainstagepage.h \
    $${SRC_GUI_DIR}/mainswitchpage.h \
    $${SRC_GUI_DIR}/mainstagemodepage.h \
    $${SRC_GUI_DIR}/lightcontrolpage.h \
    $${SRC_GUI_DIR}/switchcontrolpage.h \
    $${SRC_GUI_DIR}/airconditioningcontrolpage.h \
    $${SRC_GUI_DIR}/acscheduleset.h \
    $${SRC_GUI_DIR}/heatingcontrolpage.h \
    $${SRC_GUI_DIR}/curtainscontrolpage.h \
    $${SRC_GUI_DIR}/simulatehomesettings.h \
    $${SRC_GUI_DIR}/stagesettingspage.h \
    $${SRC_GUI_DIR}/systemmain.h \
    $${SRC_SETTINGS_DIR}/regionalsettings.h \
    $${SRC_SETTINGS_DIR}/datetimesettings.h \
    $${SRC_SETTINGS_DIR}/propertiessettings.h \
    $${SRC_SETTINGS_DIR}/calibrationdialog.h \
    $${SRC_SETTINGS_DIR}/scribblewidget.h
