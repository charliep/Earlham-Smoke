#!/bin/sh

# unkown_opt.sh
# 
#
# Created by Gilbert Bailey on 3/26/10.
# Copyright 2010 Earlham College. All rights reserved.
EXPECTED_ARGS=1

if [ $# -ne $EXPECTED_ARGS ]
then
  echo "Usage: `basename $0` <file.out>"
  exit $E_BADARGS
fi

OUTPUT=$1

../../Smoke -f > outputs/$OUTPUT

exit 0


