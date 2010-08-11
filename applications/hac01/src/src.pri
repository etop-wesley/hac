
THIS_DIR = src

INCLUDEPATH += $${THIS_DIR}
LIBS +=

SOURCES += $${THIS_DIR}/main.cpp

HEADERS += $${THIS_DIR}/hac-config.h \

include (gui/gui.pri)
include (model/model.pri)
include (settings/settings.pri)
include (device/device.pri)
