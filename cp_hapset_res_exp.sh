#!/bin/sh

# copy $1/rtool_res_hapset to $1/rtool_exp_hapset. THis will delete the exepcted results if they exist

if [ -z "$1" ]
then
  echo "Error: please pass directory as first argument"
  exit 1
fi

if [ ! -d "$1" ]
then
  echo "Error: not a directory: $1"
  exit 1
fi

HAPSET_RES=${1}/rtool_res_hapset

if [ ! -d $HAPSET_RES ]
then
  echo "Error: unable to find hapset results: $HAPSET_RES"
  exit 1
fi

HAPSET_EXP=${1}/rtool_exp_hapset

rm -rf $HAPSET_EXP || exit 1

cp -r $HAPSET_RES $HAPSET_EXP || exit 1
