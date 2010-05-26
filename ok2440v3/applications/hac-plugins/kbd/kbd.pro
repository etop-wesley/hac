TEMPLATE = lib
TARGET = ../build/hac-kbd
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qt plugin

QT -= network

# Input
HEADERS +=	hackbddriverplugin.h \
		armsys2440keyboardhandler.h
SOURCES +=	hackbddriverplugin.cpp \
		armsys2440keyboardhandler.cpp

rootfs.path = /${ROOTFS_INSTALL}/opt/Qt/plugins/kbddrivers
rootfs.files = ../build/*
INSTALLS += rootfs

QMAKE_CLEAN += ../build/* ./Makefile ../Makefile
