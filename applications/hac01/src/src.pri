
THIS_DIR = src

INCLUDEPATH += $${THIS_DIR}
LIBS +=

SOURCES += $${THIS_DIR}/main.cpp

HEADERS += $${THIS_DIR}/config.h \

include (gui/gui.pri)
include (model/model.pri)
#include (device/device.pri)
