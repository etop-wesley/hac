#!/bin/sh

if [ "$#" != "3" ]; then
	echo "Usage: steal-dir <steal file name> <his dir> <your dir>"
	exit 1;
fi

STEAL_NAME=$1
HIS_DIR=$2
YOUR_DIR=$3

echo "copying all $STEAL_DIR from $HIS_DIR to $YOUR_DIR"

cd $HIS_DIR

MATCH_LIST=`find -name "$STEAL_NAME"`

mkdir -pv $YOUR_DIR

for his in $MATCH_LIST; do
	IS_SUB=`echo $his | grep "/$STEAL_NAME/"`
	if [ "$IS_SUB" == "" ]; then
		your=${his/#.}
		your=${your////-}
		your=${your/#-}
		mkdir -pv $YOUR_DIR/$your
		cp -rfv $his/* $YOUR_DIR/$your
	fi
done

echo "happy now !"

exit 0
