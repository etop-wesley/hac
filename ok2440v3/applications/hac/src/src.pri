
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
    $${SRC_GUI_DIR}/mainhomepage.cpp \
    $${SRC_GUI_DIR}/mainfanpage.cpp \
    $${SRC_GUI_DIR}/mainheatingpage.cpp \
    $${SRC_GUI_DIR}/mainlightingpage.cpp \
    $${SRC_GUI_DIR}/mainswitchpage.cpp \
    $${SRC_GUI_DIR}/mainsystempage.cpp \
    $${SRC_GUI_DIR}/fansettings.cpp \
    $${SRC_GUI_DIR}/fanscheduleset.cpp \
    $${SRC_GUI_DIR}/fanscheduleitempick.cpp \
    $${SRC_GUI_DIR}/heatingsettings.cpp \
    $${SRC_GUI_DIR}/lightingscheduleset.cpp \
    $${SRC_GUI_DIR}/lightingscheduleitempick.cpp \
    $${SRC_GUI_DIR}/lightingstageselect.cpp \
    $${SRC_GUI_DIR}/switchscheduleset.cpp \
    $${SRC_GUI_DIR}/switchscheduleitempick.cpp \
    $${SRC_GUI_DIR}/switchscheduledelaypick.cpp \
    $${SRC_SETTINGS_DIR}/passwordquerydialog.cpp \
    $${SRC_SETTINGS_DIR}/calibrationdialog.cpp \
    $${SRC_SETTINGS_DIR}/scribblewidget.cpp \
    $${SRC_MODEL_DIR}/fanscheduleitemdata.cpp \
    $${SRC_MODEL_DIR}/lightingscheduleitemdata.cpp \
    $${SRC_MODEL_DIR}/switchscheduleitemdata.cpp


HEADERS += $${SRC_DIR}/hac-config.h \
    $${SRC_GUI_DIR}/hacapplication.h \
    $${SRC_GUI_DIR}/haccore.h \
    $${SRC_GUI_DIR}/hacmainwindow.h \
    $${SRC_GUI_DIR}/mainhomepage.h \
    $${SRC_GUI_DIR}/mainfanpage.h \
    $${SRC_GUI_DIR}/mainheatingpage.h \
    $${SRC_GUI_DIR}/mainlightingpage.h \
    $${SRC_GUI_DIR}/mainswitchpage.h \
    $${SRC_GUI_DIR}/mainsystempage.h \
    $${SRC_GUI_DIR}/fansettings.h \
    $${SRC_GUI_DIR}/fanscheduleset.h \
    $${SRC_GUI_DIR}/fanscheduleitempick.h \
    $${SRC_GUI_DIR}/heatingsettings.h \
    $${SRC_GUI_DIR}/lightingscheduleset.h \
    $${SRC_GUI_DIR}/lightingscheduleitempick.h \
    $${SRC_GUI_DIR}/lightingstageselect.h \
    $${SRC_GUI_DIR}/switchscheduleset.h \
    $${SRC_GUI_DIR}/switchscheduleitempick.h \
    $${SRC_GUI_DIR}/switchscheduledelaypick.h \
    $${SRC_SETTINGS_DIR}/passwordquerydialog.h \
    $${SRC_SETTINGS_DIR}/calibrationdialog.h \
    $${SRC_SETTINGS_DIR}/scribblewidget.h \
    $${SRC_MODEL_DIR}/fanscheduleitemdata.h \
    $${SRC_MODEL_DIR}/lightingscheduleitemdata.h \
    $${SRC_MODEL_DIR}/switchscheduleitemdata.h
