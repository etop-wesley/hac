
SRC_DIR = src

INCLUDEPATH += $${SRC_DIR}
LIBS +=

include(widgets/widgets.pri)
include(channels/channels.pri)
include(utils/utils.pri)

# widgets
SOURCES +=	

HEADERS +=	$${SRC_DIR}/hac-config.h \
		$${SRC_DIR}/hacwidgetsglobal.h

