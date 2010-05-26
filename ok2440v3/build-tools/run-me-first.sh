#!/bin/sh
##############################################################################
# script to set up build environment.
##############################################################################

if [ `dirname $0` != "./build-tools" ] && [ `dirname $0` != "build-tools" ];
then
    echo
    echo "WHOOPS, you must run me from within parent directory of 'build-tools',"
    echo "thus something like './build-tools/`basename $0`' will work."
    echo
    exit 1
fi

if [ "$#" -gt "0" ]; then
    echo "`basename $0`: No options allowed"
    exit 1
fi


PROJECT_ROOT=${PWD}

sed -e "s/WHERE_IS_PROJECT/$(echo "${PROJECT_ROOT}" | sed 's/\//\\\//g')/" build-tools/project-env > ${PROJECT_ROOT}/project-env

echo ''
echo 'project build system environment is now successfully setup'
echo 'as "project-env", please source the environment by'
echo '"source project-env"'
echo ''

exit 0

