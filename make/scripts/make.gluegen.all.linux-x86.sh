#! /bin/sh

SDIR=`dirname $0` 

if [ -e $SDIR/setenv-build-jogamp-x86.sh ] ; then
    . $SDIR/setenv-build-jogamp-x86.sh
fi

#    -Dc.compiler.debug=true 
#    -Dgluegen.cpptasks.detected.os=true \
#    -DisUnix=true \
#    -DisLinux=true \
#    -DisLinuxX86=true \
#    -DisX11=true \
#    -Dgluegen-cpptasks.file=`pwd`/lib/gluegen-cpptasks-linux-32bit.xml \
#

#export JOGAMP_JAR_CODEBASE="Codebase: *.jogamp.org"
export JOGAMP_JAR_CODEBASE="Codebase: *.goethel.localnet"

ant \
    -Drootrel.build=build-x86 \
    $* 2>&1 | tee make.gluegen.all.linux-x86.log
