#!/bin/sh

# test_driver.sh
# Created by Gilbert Bailey on 3/6/10.
# Copyright 2010 Earlham College. All rights reserved.

EXPECTED_ARGS=3
E_BADARGS=47

if [ $# -ne $EXPECTED_ARGS ]
then
  echo "Usage: `basename $0` <scripts_dir> <canon_dir> <outputs_dir>"
  exit $E_BADARGS
fi

scripts_dir=$1
canon_dir=$2
outputs_dir=$3

echo "Your scripts directory is $scripts_dir"
echo "Your canon directory is $canon_dir"
echo "Your canon directory is $outputs_dir"


cd $scripts_dir

for file in `ls *.sh` ; do
  ./$file "$file".out 
done

diff $canon_dir $outputs_dir > diff.out

#if [ -s diff.out ]
  #Mail here
#fi

cd $outputs_dir
rm *
cd ../..
  
exit 0