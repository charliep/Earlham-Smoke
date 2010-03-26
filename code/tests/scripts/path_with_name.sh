#!/bin/sh

# path_with_name.sh
# 
#
# Created by Gilbert Bailey on 3/23/10.
# Copyright 2010 Earlham College. All rights reserved.
EXPECTED_ARGS=1

if [ $# -ne $EXPECTED_ARGS ]
then
  echo "Usage: `basename $0` <file.out>"
  exit $E_BADARGS
fi

OUTPUT=$1

../../Smoke smoke_path > outputs/$OUTPUT

exit 0

