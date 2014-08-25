#!/bin/bash

# Directory holding output dtrace files to be processed by daikon
RTOOL_OUT=arijit

# Name of the class where daikon's main file is
DAIKON_CLASS=daikon.Daikon

# JVM to use
JAVA=java

# Directory to hold invariants learned by RTool using DPOR
RTOOL_DPOR_RES=rtool_res_dpor

# Directory holding expected DPOR results
RTOOL_EXP_DPOR=rtool_exp_dpor

# The Kvasir output location
KVASIR_OUT=arijit/output_1.dtrace

# Directory to hold output of kvasir+daikon
DAIK_RES=daik_res

# number of reps of daikon to run
DAIK_REPS=1

# location where extract_time() saves time output 
TIME_OUTPUT=time.out

# Command use to time tests. Currently, this is the elapsed real time in seconds
TIME="`which time` -f %e"

# Passed argument is assumed to be a string which is a float of the time
# desired to add to the TIME_OUTPUT file. If the TIME_OUTPUT file does not
# exist, the passed time is simply put into the TIME_OUTPUT file
extract_time_and_add() {
  if [ -z "$1" ]
  then
    echo "Error: extract time passed no first argument"
    exit 1
  fi

  if [ ! -f "$TIME_OUTPUT" ]
  then
    # if the time output does not exist, then initialize it to zero
    echo '0'  >$TIME_OUTPUT
  fi

  # extract the new real time from the passed file. It is the first line prefixed with 'real: '
  echo "[DEBUG] Passed Time: $1" || exit 1
  CUR_TIME=`cat $TIME_OUTPUT`
  echo "[DEBUG] Old Time: $CUR_TIME"
  echo "$1 + $CUR_TIME" | bc > $TIME_OUTPUT || exit 1
  echo "Post bc: " 
  cat $TIME_OUTPUT
}

# This should be called between each individual test (e.g., between DPOR and
# HaPSet
cleanup_between_tests() {
  rm -rf arijit/
  rm time.out
}

# count the numebr of invariants generated. The passed argument should be a
# directory containing files ending in ".out" which are filled with invariants
count_inv() {
  if [ -z $1 ]
  then
    echo "Error: count_inv() must be passed a directory as argument one"
    exit 1
  fi

# remove lines in the file which are not actually invariants
cat ${1}/*.out \
| sed \
'/===========================================================================/d' \
| sed '/.\+:::EXIT/d' | sed '/.\+:::ENTER/d' | sed '/Exiting Daikon\./d'\
| sed '/^[[:space:]]*$/d' | wc -l > ${1}/num_inv
}

# $1 should be a directory to test

if [ -z "$1" ]
then
  echo "Error: Please pass directory to test as first argument"
  exit 1
fi


cd $1 || exit 1

# clean up old results
controller_ui.py rtool clean

# Run daikon ==================================================================
# Daikon should be run first since the RTool compiliation process creates some
# intermediate C files. These confuse the compilation phase for daikon
echo "Running Daikon on test $1"
# Compile and run test
($TIME controller_ui.py daikon rep $DAIK_REPS) 2>kvas.stderr.out
# double check that any old time file is not around
rm -f $TIME_OUTPUT
extract_time_and_add `tail -n 1 kvas.stderr.out`

# Process results with daikon
mkdir -p $DAIK_RES || exit 1
OUTPUT_FILE=$DAIK_RES/daik.out

($TIME $JAVA daikon.Daikon $KVASIR_OUT >$OUTPUT_FILE) 2>daik.stderr.out
extract_time_and_add `tail -n 1 daik.stderr.out`

# count the number of invariants. This should be done before we move the time
# file since it also ends in .out!
count_inv $DAIK_RES
# move time file to results directory
mv $TIME_OUTPUT $DAIK_RES

# Finish daikon test ==========================================================

cleanup_between_tests

# Run DPOR on test ============================================================
echo "Running DPOR on test $1"
# double check that any old time file is not around
rm -f $TIME_OUTPUT
($TIME controller_ui.py rtool comp) 2>comp.stderr.out
extract_time_and_add `tail -n 1 comp.stderr.out`
# keep track of the time to run the test
($TIME controller_ui.py rtool run 0 0 0) 2> dpor.stderr.out
# last line of stderr is the output of time
extract_time_and_add `tail -n 1 dpor.stderr.out`


TRACES=`ls $RTOOL_OUT`
for f in $TRACES
do
  echo "Running on trace $f"
  # location where RTool invariants will be stored
  OUTPUT_FILE=${RTOOL_DPOR_RES}/${f}.rtool.out
  # location where epxected results are stored
  EXPECTED_FILE=${RTOOL_EXP_DPOR}/${f}.rtool.out

  mkdir -p $RTOOL_DPOR_RES || exit 1

  # we are chop off the first 3 lines (they contain the time the test was run).
  # We also need to add the time used in this step to the time to actually run the tests
  ($TIME java $DAIKON_CLASS "${RTOOL_OUT}/$f" | sed -e '1,3d' > ${OUTPUT_FILE}) 2>daikon.stderr.out
  extract_time_and_add `tail -n 1 daikon.stderr.out`

  # next, check if the results match the expected
  echo "[DEBUG] Output file: ${OUTPUT_FILE}"
  echo "[DEBUG] Expected File: ${EXPECTED_FILE}"
  diff ${OUTPUT_FILE} $EXPECTED_FILE
  ret=$?

  if [ $ret -ne 0 ]
  then
    echo "$(tput setaf 1)Warning: Expected results do not match$(tput sgr0)"
  fi

done

# Count the number of invariants generated. This big sed command removes lines which are not invariants
#cat ${RTOOL_DPOR_RES}/*.out | sed '/===========================================================================/d' | sed '/.\+:::EXIT/d' | sed '/.\+:::ENTER/d' | sed '/Exiting Daikon\./d' | wc -l > ${RTOOL_DPOR_RES}/num_inv
count_inv ${RTOOL_DPOR_RES}

# Save the total time to run over all the files
mv $TIME_OUTPUT ${RTOOL_DPOR_RES}/
# Finish DPOR Test ============================================================


# Return to the parent directory.
cd ..
