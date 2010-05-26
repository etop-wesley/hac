
SRC_DIR = src

INCLUDEPATH += $${SRC_DIR}
LIBS +=

SOURCES +=	$${SRC_DIR}/calibrationdialog.cpp \
		$${SRC_DIR}/choosesetdatetimewidget.cpp \
		$${SRC_DIR}/choosecreateeditschedulewidget.cpp \
		$${SRC_DIR}/enterpasswordwidget.cpp \
		$${SRC_DIR}/settimewidget.cpp \
		$${SRC_DIR}/setvocationdatewidget.cpp \
		$${SRC_DIR}/helpwidget.cpp \
		$${SRC_DIR}/scribblewidget.cpp

HEADERS +=	$${SRC_DIR}/calibrationdialog.h \
		$${SRC_DIR}/scribblewidget.h \
		$${SRC_DIR}/choosesetdatetimewidget.h \
		$${SRC_DIR}/choosecreateeditschedulewidget.h \
		$${SRC_DIR}/enterpasswordwidget.h \
		$${SRC_DIR}/settimewidget.h \
		$${SRC_DIR}/setvocationdatewidget.h \
		$${SRC_DIR}/helpwidget.h \
		$${SRC_DIR}/hacsettings-config.h

