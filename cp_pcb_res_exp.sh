#!/bin/sh

# copy $1/rtool_res_pcb to $1/rtool_exp_pcb. THis will delete the exepcted results if they exist

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

PCB_RES=${1}/rtool_res_pcb

if [ ! -d $PCB_RES ]
then
  echo "Error: unable to find hapset results: $PCB_RES"
  exit 1
fi

PCB_EXP=${1}/rtool_exp_pcb

rm -rf $PCB_EXP || exit 1

cp -r $PCB_RES $PCB_EXP || exit 1
