
SRC_DIR = src

INCLUDEPATH += $${SRC_DIR}
LIBS +=

SOURCES +=	$${SRC_DIR}/hachelp.cpp \
                $${SRC_DIR}/haclistwidget.cpp \
                $${SRC_DIR}/hacdatetimelabel.cpp \
                $${SRC_DIR}/hacwaitbox.cpp \
                $${SRC_DIR}/hacled.cpp

HEADERS +=	$${SRC_DIR}/hac-config.h \
		$${SRC_DIR}/hacwidgetsglobal.h \
		$${SRC_DIR}/hachelp.h \
                $${SRC_DIR}/haclistwidget.h \
                $${SRC_DIR}/hacdatetimelabel.h \
                $${SRC_DIR}/hacwaitbox.h \
                $${SRC_DIR}/hacled.h



