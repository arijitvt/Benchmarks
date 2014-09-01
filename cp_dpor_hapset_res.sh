#!/bin/sh

# copy $1/rtool_exp_dpor to $1/rtool_exp_hapset

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

DPOR_EXP=${1}/rtool_exp_dpor

if [ ! -d $DPOR_EXP ]
then
  echo "Error: unable to find dpor expected: $DPOR_EXP"
  exit 1
fi

HAPSET_EXP=${1}/rtool_exp_hapset

if [ -d "$HAPSET_EXP" ]
then
  echo "Error: HaPSet results already exist: $HAPSET_EXP"
  exit 1
fi

cp -r $DPOR_EXP $HAPSET_EXP || exit 1
