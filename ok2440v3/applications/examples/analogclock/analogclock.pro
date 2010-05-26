HEADERS       = analogclock.h
SOURCES       = analogclock.cpp \
                main.cpp

# install
target.path = /${ROOTFS_INSTALL}/usr/bin
INSTALLS += target
