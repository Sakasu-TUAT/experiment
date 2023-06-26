#!/bin/sh
FILENAME=$1
SPLITNAME=${FILENAME%.*}
./znc < $FILENAME > $SPLITNAME.s
cp $SPLITNAME.s ../znas
cd ../znas
./znas < $SPLITNAME.s > $SPLITNAME.p3
cp $SPLITNAME.p3 ../p386
cd ../p386
./p386 $SPLITNAME.p3
cd ../zinc-0