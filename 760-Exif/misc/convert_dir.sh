#!/bin/bash

SIZE=256
DIR=medium

if test $# -ne 1 || ! test -d $1
then
    echo Usage: $0 KATALOG_Z_FOTKAMI
    exit 1
fi

if test -d $DIR
then
  echo directory $DIR exists .. continuing ...
else
  mkdir $DIR
fi

for photo in $1/*.jpg ; do
    echo converting $(basename $photo) ...
    identify $photo
    convert -geometry ${SIZE}x${SIZE} $photo $DIR/$(basename $photo)
    identify $DIR/$(basename $photo)
done
