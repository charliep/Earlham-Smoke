#!/bin/sh

# log_with_file.sh
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

../../Smoke -l log_test > outputs/$OUTPUT

exit 0


