#!/bin/sh

# copy $1/rtool_exp_dpor to $1/rtool_exp_cpb

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

PCB_EXP=${1}/rtool_exp_pcb

if [ -d "$PCB_EXP" ]
then
  echo "Error: PCB results already exist: $PCB_EXP"
  exit 1
fi

cp -r $DPOR_EXP $PCB_EXP || exit 1
