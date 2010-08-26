
THIS_DIR = src

INCLUDEPATH += $${THIS_DIR}
LIBS +=

SOURCES +=	$${THIS_DIR}/main.cpp \
	  	$${THIS_DIR}/statusbar.cpp \
	  	$${THIS_DIR}/hacserver.cpp

HEADERS +=	$${THIS_DIR}/config.h \
	  	$${THIS_DIR}/statusbar.h \
	  	$${THIS_DIR}/hacserver.h
