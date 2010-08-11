#!/bin/bash
##############################################################################
#
# Description: script for build a package
#
# Author: wesley.xie (elelonger@gmail.com)
# version: 1.0
#
##############################################################################

set -e

if [ -z ${PROJECT} ]; then
	echo "Please setup the project environment firstly. (Enter project root and \"source project-env\"" && exit 1;
fi

# directories
BUILD_DIR=${PROJECT_BUILD_INSTALL}
ROOTFS_DIR=${ROOTFS}
PKGTOOL_DIR=${PROJECT_ROOT}/build-tools/package

# images
LOADER_IMG=u-boot.bin
PARAM_IMG=param.bin
SPLASH_IMG=splash.bmp
KERNEL_IMG=uImage.img
ROOT_IMG=root.yaffs
#DATA_IMG=data.yaffs

PKG_IMAGES="$LOADER_IMG $PARAM_IMG $SPLASH_IMG $KERNEL_IMG $ROOT_IMG $DATA_IMG"
PKG_NAME=etop-hac01.pkg
PKG_VERSION=$1
PKG_CONFIG=etop-hac01-pkg.cfg

DATESTR=$(date +%y%m%d)

# utils
MKYAFFS2=mkyaffs2image
PKG_TOOL=package

BUILD_UTILS="$MKYAFFS2 $PKG_TOOL"
SYSTEM_UTILS="gzip"




# main entry

# check version
if [ "$1" = "" ]; then
	echo "Usage: `basename $0` <version> (1.2.3)"
	exit 1
fi

cd $BUILD_DIR

# check required utils
echo "checking utils ..."
for u in $SYSTEM_UTILS; do
	if ! which $u 1> /dev/null 2> /dev/null; then
		echo "'$u' util not found in host, please install it firstly!"
		exit 1
	fi;
done
for u in $BUILD_UTILS; do
	if [ ! -x $u ]; then
		echo "'$u' util not found in $BUILD_DIR, please install it firstly!"
		exit 1
	fi;
done

# check images
echo "checking images ..."
for img in $PKG_IMAGES; do
	if [ ! -e $img ]; then
		echo ""
		echo "$img doesn't exist, please install it firstly!"
		echo ""
	fi;
done

# compress images
#echo "compressing images ..."
#for img in $PKG_IMAGES; do
#	gzip -cv9 $img > $img.gz
#done

# generate pkg config

# build package
echo "building pakcage ..."
./$PKG_TOOL -q -c ./$PKG_CONFIG
zip -9 $PKG_NAME.zip $PKG_NAME
if [ "$?" == "0" ]; then
	echo "pakcage successfully create in $BUILD_DIR"
fi;

exit 0
