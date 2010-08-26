
THIS_DIR = src/gui

INCLUDEPATH += $${THIS_DIR}

SOURCES	+=	$${THIS_DIR}/haccore.cpp \
		$${THIS_DIR}/mainwindow.cpp \
		$${THIS_DIR}/homepage.cpp \
		$${THIS_DIR}/calendarcontrol.cpp \
		$${THIS_DIR}/autocontrolmain.cpp \
		$${THIS_DIR}/stagecontrol.cpp \
		$${THIS_DIR}/roomchoose.cpp \
		$${THIS_DIR}/accontrol.cpp \
		$${THIS_DIR}/heatingcontrol.cpp \
		$${THIS_DIR}/curtainscontrol.cpp \
		$${THIS_DIR}/lightingscontrol.cpp \
		$${THIS_DIR}/switchescontrol.cpp

HEADERS	+=	$${THIS_DIR}/haccore.h \
		$${THIS_DIR}/mainwindow.h \
		$${THIS_DIR}/homepage.h \
		$${THIS_DIR}/calendarcontrol.h \
		$${THIS_DIR}/autocontrolmain.h \
		$${THIS_DIR}/stagecontrol.h \
		$${THIS_DIR}/roomchoose.h \
		$${THIS_DIR}/accontrol.h \
		$${THIS_DIR}/heatingcontrol.h \
		$${THIS_DIR}/curtainscontrol.h \
		$${THIS_DIR}/lightingscontrol.h \
		$${THIS_DIR}/switchescontrol.h
