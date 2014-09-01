#!/bin/sh

./cp_dpor_hapset_res.sh $1 || exit 1
./cp_dpor_pcb_res.sh $1 || exit 1
