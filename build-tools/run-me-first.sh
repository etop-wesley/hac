#!/bin/sh
##########################################################################################
# setup build environment
# NOTE: this script must be run from the project root
##########################################################################################

set -e


if [ `dirname $0` != "./build-tools" ] && [ `dirname $0` != "build-tools" ]; then
        echo
        echo "WHOOPS, you must run me from within parent directory of 'build-tools',"
        echo "thus, something like './build-tools/`basename $0`' will work."
        echo
        exit 1
fi

PROJECT_ROOT=${PWD}
PROJECT_ENV=${PROJECT_ROOT}/project-env
THIS_DIR=$(dirname $0 | xargs -- readlink -f)
PROJECT_ENV_BASE=${THIS_DIR}/scripts/project-env.base

TOOLCHAIN_DIR=${PROJECT_ROOT}/toolchains

CC_PKG=$TOOLCHAIN_DIR/cross-3.4.1.tar.bz2
CC_DIR=$TOOLCHAIN_DIR/cross-3.4.1
CC_LINK=/usr/local/arm/3.4.1

help()
{
        echo
        echo "Usage: $0 <command>"
        echo "Available related command:"
        echo "    build:      setup environment"
        echo "    clean:      clean environment"
        echo "    help:       print this help"
        echo
}

clean()
{
	rm -rvf ${PROJECT_ENV}
	if [ -h "${CC_LINK}" -a "`readlink -ne ${CC_LINK}`" == "${CC_DIR}" ]; then
		if [ $UID -eq "0" ]; then rm -fv ${CC_LINK}
		else echo "you need root permission to remove link ${CC_LINK}"; su -c "rm -vf ${CC_LINK}"; fi
	fi
	rm -rvf ${CC_DIR}
}

build()
{
	if [ ! -d "${CC_DIR}" ]; then
		mkdir -pv ${CC_DIR}
		echo "unpack the cross toolchain package ..."
		tar -C ${CC_DIR} --strip-components 4 -xzvf ${CC_PKG}
	fi

	if [ -h "${CC_LINK}" -a "`readlink -ne ${CC_LINK}`" == "${CC_DIR}" ]; then :
	else
		echo "fixing arm-linux-gcc installation problem ..."
		if [ $UID -eq "0" ]; then
			mkdir -pv `dirname ${CC_LINK}` && ln -Tsvf ${CC_DIR} ${CC_LINK}
		else
			echo "you need root permission to create link ${CC_LINK}"
			su -c "mkdir -p `dirname ${CC_LINK}` && ln -Tsvf ${CC_DIR} ${CC_LINK}"
		fi
	fi

	sed -e "s/WHERE_IS_PROJECT/$(echo "${PROJECT_ROOT}" | sed 's/\//\\\//g')/" ${PROJECT_ENV_BASE} > ${PROJECT_ENV}

	echo
	echo "##############################################################"
	echo "project build system environment is ready now."
	echo "please source the environment by 'source project-env'."
	echo "##############################################################"
	echo
}


# main entry
if [ "$#" -lt "1" ]; then
	help
else
	case $1 in
	"help")
		help
		;;
	"build")
		build
		;;
	"clean")
		clean
		;;
	*)
		help
		;;
	esac
fi

exit 0
