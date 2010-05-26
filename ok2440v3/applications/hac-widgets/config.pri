######################################################################
# Install paths
######################################################################

VER_MAJ      = 1
VER_MIN      = 1
VER_PAT      = 0

VERSION      = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

CONFIG(host) {
    unix {
        INSTALLBASE    = /usr

	target.path    = $$INSTALLBASE/lib
	headers.path   = $$INSTALLBASE/include
	doc.path       = $$INSTALLBASE/doc

    }
    win32 {
        INSTALLBASE    = $$[QT_INSTALL_PREFIX]


	target.path    = $$INSTALLBASE/bin
	headers.path   = $$INSTALLBASE/include
	doc.path       = $$INSTALLBASE/doc

    }

} else {
    # target system
    target.path	= /${ROOTFS_INSTALL}/usr/lib
    toolchain_include.path = /${TOOLCHAIN_USR_INSTALL}/usr/include
    toolchain_lib.path = /${TOOLCHAIN_USR_INSTALL}/usr/lib

}
######################################################################
# qmake internal options
######################################################################

CONFIG           += qt     # Also for Qtopia Core!
CONFIG           += warn_on
#CONFIG           += thread

######################################################################
# release/debug mode
# If you want to build both DEBUG_SUFFIX and RELEASE_SUFFIX
# have to differ to avoid, that they overwrite each other.
######################################################################

VVERSION = $$[QT_VERSION]
isEmpty(VVERSION) {

    # Qt 3
    CONFIG           += release     # release/debug
}
else {
    # Qt 4
    win32 {
        # On Windows you can't mix release and debug libraries.
        # The designer is built in release mode. If you like to use it
        # you need a release version. For your own application development you
        # might need a debug version. 
        # Enable debug_and_release + build_all if you want to build both.

        CONFIG           += release     # release/debug/debug_and_release
        #CONFIG           += release_and_release
        #CONFIG           += build_all
    }
    else {
        CONFIG           += release     # release/debug
    }
}

######################################################################
# If you want to have different names for the debug and release 
# versions you can add a suffix rule below.
######################################################################

DEBUG_SUFFIX        = 
RELEASE_SUFFIX      = 

win32 {
    DEBUG_SUFFIX      = d
}

######################################################################
# Build the static/shared libraries.
# If Dll is enabled, a shared library is built, otherwise
# it will be a static library.
######################################################################

CONFIG	+= Dll

######################################################################
# HacWidgets enables all classes
#
######################################################################

CONFIG	+= Widgets

######################################################################
# If you want to build the designer plugin, 
# enable the line below.
# Otherwise you have to build it from the designer directory.
######################################################################

#CONFIG	+= Designer

######################################################################
# If you want to auto build the examples, enable the line below
# Otherwise you have to build them from the examples directory.
######################################################################

#CONFIG	+= Examples
