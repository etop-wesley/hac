#!/bin/sh
###################################################################################
# mtk168 build help script
#
# Initial creation ---------------------- 02-25-2009 wesley.xie elelonger@gmail.com
#
###################################################################################

# force exit on errors
set -e

PROJECT_NAME=OK2440
PROJECT_ROOT=${PWD}

BSP_DIR=${PROJECT_ROOT}/bsp
SCRIPTS_DIR=${BSP_DIR}/scripts
IMAGES_DIR=${BSP_DIR}/images
EXTERNAL_LIBS_DIR=${PROJECT_ROOT}/external-components
LIBS_DIR=${PROJECT_ROOT}/libraries
EXTRA_APPS_DIR=${PROJECT_ROOT}/extra-applications
APPS_DIR=${PROJECT_ROOT}/applications

PROJECT_ENV=${PROJECT_ROOT}/project-env

help()
{
	echo
	echo "Usage: `basename $0` <command> [options]"
	echo "Available build related command:"
	echo "    all:        clean, make and install in the right order"
	echo "    install:    install all files to rootfs"
	echo "    clean:      clean objects"
	echo "    upk:        make update package"
	echo "    help:       print this help"
	echo "Avaiable options: not support yet"
	echo
}

help_env()
{
	echo
	echo "To develop with $PROJECT_NAME platform, there are somethings need to be done firstly"
	echo "1. go to your project root, and run './bsp/scripts/build-env.sh build' to build the toolchain environment"
	echo "2. go to your project root, and run 'source project-env' to source the environment"
	echo "3. go to your project root, and run './build-helper.sh all' to build the entire project"
	echo "4. please 'source project-env' when you run a new terminal window if need"
	echo
}

make_bsp()
{
	echo "make and install bsp ..."
	pushd ${BSP_DIR}
	make rebuild
	popd
}

make_external_libs()
{
	echo "make and install external libs ..."
	pushd ${EXTERNAL_LIBS_DIR}
	make rebuild
	popd
}

make_libs()
{
	echo "make and install libs ..."
	pushd ${LIBS_DIR}
	make rebuild
	popd
}

make_extra_apps()
{
	echo "make and install extra apps ..."
	pushd ${EXTRA_APPS_DIR}
	make rebuild
	popd
}

make_apps()
{
	echo "make and install apps ..."
	pushd ${APPS_DIR}
	make rebuild
	popd
}

make_upk()
{
	echo "make upk ..."
	echo -n "Please input the release version(for example: 1.2.3): "
	read version
	${SCRIPTS_DIR}/make-upk.sh $version
}

# main entry
if [ "$#" -lt "1"  ]; then
	help
else
	if [ ! -f "${PROJECT_ENV}" ]; then
		help_env
		exit 1
	fi

	source ${PROJECT_ENV}
	case $1 in
	"all")
		echo "make and install everything ..."
		make_bsp
		make_external_libs
		make_libs
		make_extra_apps
		make_apps
		;;
	"install")
		echo install
		;;
	"clean")
		echo clean
		;;
	"upk")
		make_upk
		;;
	*)
		help
		;;
	esac
fi

exit 0
