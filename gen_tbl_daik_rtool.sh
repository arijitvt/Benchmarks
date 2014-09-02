#/bin/bash

# error on undefined
set -e
# error on unset
set -u

# Generate a table entry for comparing daikon vs R_Tool for passed test directory
PROG_POINTS_FILE=ProgramPoints.ppts
RTOOL_DPOR_RES=rtool_res_dpor
RTOOL_HAPSET_RES=rtool_res_hapset
DAIK_RES=daik_res

# Directory to hold invariants learned by RTool using PCB 2
RTOOL_PCB_RES=rtool_res_pcb
# Directory holding expected PCB results
RTOOL_EXP_PCB=rtool_exp_pcb

if [ -z ${1+x} ]
then
  echo "Error: first argument should be a directory"
  exit 1
fi

if [ ! -d "$1" ]
then
  echo "Error: directory does not exist: $1"
  exit 1
fi

# Name of the test is the directory name (remove trailing slash if it exists)
NAME=${1%/}
cd $1 || exit 1
if [ ! -f $PROG_POINTS_FILE ]
then
  echo "Error: program points file does not exist: $PROG_POINTS_FILE"
  exit 1
fi

# count the number of program points. The first line is a header for the module or something. Remove lines only containing whitespace too.
PRG_POINTS=`cat $PROG_POINTS_FILE | sed '1d' | sed ''/^[[:space:]]*$/d'' | wc -l`
# Cant do this automatically
GLOBALS="???"

DAIK_TTL_INV=`cat $DAIK_RES/num_inv`

# Wish this could be done automatically....
INC_INV="???"
CORRECT_INV="???"

DAIK_TIME=`cat $DAIK_RES/time.out`
DAIK_NUM_RUNS=`cat $DAIK_RES/num_runs`

HAPSET_TTL_INV=`cat $RTOOL_HAPSET_RES/num_inv`
HAPSET_NUM_RUNS=`cat $RTOOL_HAPSET_RES/num_runs`
HAPSET_TIME=`cat $RTOOL_HAPSET_RES/time.out`

# some tests do not test DPOR, for this case, fill the results with "\xmark"
if [ ! -d "$RTOOL_DPOR_RES" ]
then
  DPOR_TTL_INV="\\xmark"
  DPOR_NUM_RUNS="\\xmark"
  DPOR_TIME="\\xmark"
else
  DPOR_TTL_INV=`cat $RTOOL_DPOR_RES/num_inv`
  DPOR_NUM_RUNS=`cat $RTOOL_DPOR_RES/num_runs`
  DPOR_TIME=`cat $RTOOL_DPOR_RES/time.out`
fi

PCB_TTL_INV=`cat $RTOOL_PCB_RES/num_inv`
PCB_NUM_RUNS=`cat $RTOOL_PCB_RES/num_runs`
PCB_TIME=`cat $RTOOL_PCB_RES/time.out`

# Just daikon + hapset
#echo "$NAME &  $PRG_POINTS & $GLOBALS & $NUM_RUNS & $DAIK_TTL_INV & $INC_INV & $DAIK_TIME & $HAPSET_TTL_INV & $CORRECT_INV & $HAPSET_TIME"

# daikon + hapset + pcb + dpor
#echo "$NAME &  $PRG_POINTS & $GLOBALS &  $DAIK_TTL_INV & $INC_INV & $DAIK_NUM_RUNS & $DAIK_TIME & $HAPSET_TTL_INV & $CORRECT_INV & $HAPSET_NUM_RUNS & $HAPSET_TIME & $PCB_TTL_INV & $CORRECT_INV & $PCB_NUM_RUNS & $PCB_TIME & $DPOR_TTL_INV & $CORRECT_INV & $DPOR_NUM_RUNS & $DPOR_TIME \\\\"

echo "$NAME &  $PRG_POINTS & $GLOBALS &  $DAIK_TTL_INV & $HAPSET_TTL_INV & $PCB_TTL_INV & $DPOR_TTL_INV & $CORRECT_INV & $CORRECT_INV & $CORRECT_INV & $CORRECT_INV & $DAIK_NUM_RUNS & $HAPSET_NUM_RUNS & $PCB_NUM_RUNS & $DPOR_NUM_RUNS & $DAIK_TIME & $HAPSET_TIME & $PCB_TIME & $DPOR_TIME \\\\"
