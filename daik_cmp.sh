#!/bin/bash

set -u

if [ -z ${1+x} ]
then
  echo "Pass arg 1 (directory)"
  exit 1
fi

if [ -z ${2+x} ]
then
  echo "Pass arg 2 (num reps)"
  exit 1
fi

if [ -z ${3+x} ]
then
  echo "Pass arg 3 (num reps)"
  exit 1
fi

if [ ! -d "$1" ]
then
  echo "Error: not a directory: $1"
fi

RES_1=$1/daik_res_$2/daik.out
RES_2=$1/daik_res_$3/daik.out

if [ ! -f $RES_1 ]
then
  echo "Error: file not found: $RES_1"
  exit 1
fi

if [ ! -f $RES_2 ]
then
  echo "Error: file not found: $RES_2"
  exit 1
fi

diff $RES_1 $RES_2 || exit 1
