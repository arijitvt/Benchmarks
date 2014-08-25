#/bin/bash

# Generate a table entry for comparing daikon vs R_Tool for passed test directory
# Table entry has the following columns: 
#  Name & Program Points & Global Vars. & Total Inv. & Correct Inv. & Incorrect Inv. & Time (s) & Total Inv. & Correct Inv. & Incorrect Inv. & Time (s) \\
# Columns which require human intervention will be filled with "???"

PROG_POINTS_FILE=ProgramPoints.ppts
RTOOL_DPOR_RES=rtool_res_dpor
DAIK_RES=daik_res

if [ -z "$1" ]
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
CORRECT_INV="???"
INC_INV="???"
DAIK_TIME=`cat $DAIK_RES/time.out`

DPOR_TTL_INV=`cat $RTOOL_DPOR_RES/num_inv`
DPOR_TIME=`cat $RTOOL_DPOR_RES/time.out`

echo "$NAME &  $PRG_POINTS & $GLOBALS & $DAIK_TTL_INV & $CORRECT_INV & $INC_INV & $DAIK_TIME & $DPOR_TTL_INV & $CORRECT_INV & $INC_INV & $DPOR_TIME"
