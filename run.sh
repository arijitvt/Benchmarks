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

# Directory to hold invariants learned by RTool using HaPSet
RTOOL_HAPSET_RES=rtool_res_hapset
# Directory holding expected DPOR results
RTOOL_EXP_HAPSET=rtool_exp_hapset

# The Kvasir output location
KVASIR_OUT=arijit/output_1.dtrace

# Directory to hold output of kvasir+daikon
DAIK_RES=daik_res

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
  rm -f time.out
  rm hook.*
}

# Remove the daikon header (first three lines) and footer (last line) from the
# passed file
remove_daik_header_footer() {
  if [ -z "$1" ]
  then
    echo "Error: remove_daik_header_footer() requires one argument"
    exit 1
  fi

  if [ ! -f "$1" ] 
  then
    echo "Error: remove_daik_header_footer(): file does not exist: $f"
    exit 1
  fi

  # remove first three lines
  sed -i '1,3d' $1
  # remove last line
  sed -i '$ d' $1

  # remove unterminated calls 
  sed -i '/Unterminated calls:/d' $1
  sed -i '/No return from procedure observed.*/d' $1
  sed -i '/.*Unmatched entries are ignored.*/d' $1
  sed -i '/.*Finished reading.*/d' $1
  sed -i '/.*: [[:digit:]]\+ invocation.*/d' $1
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
'/.*===========================================================================/d' \
| sed '/.\+:::EXIT/d' | sed '/.\+:::ENTER/d' | sed '/Exiting Daikon\./d'\
| sed '/^[[:space:]]*$/d' | wc -l > ${1}/num_inv
}

# $1 should be the standard output of Inspect. This will create a file num_runs
# with the number of runs performed by inspect
count_num_runs() {
  if [ -z "$1" ] 
  then
    echo "Error: count_num_runs() must be passed a file as argument one"
    exit 1
  fi
  grep 'Total number of runs: ' hapset.stdout.out | cut -d':' -f2 | cut -c 2- >num_runs
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



# Run HaPSet on test ============================================================
echo "Running HaPSet on test $1"
# double check that any old time file is not around
rm -f $TIME_OUTPUT
#($TIME controller_ui.py rtool comp) 2>comp.stderr.out
#extract_time_and_add `tail -n 1 comp.stderr.out`
# keep track of the time to run the test
($TIME controller_ui.py rtool run 0 2 1) 2> hapset.stderr.out 1>hapset.stdout.out
# last line of stderr is the output of time
extract_time_and_add `tail -n 1 hapset.stderr.out`
count_num_runs "hapset.stdout.out"

TRACES=`ls $RTOOL_OUT`
for f in $TRACES
do
  echo "Running on trace $f"
  # location where RTool invariants will be stored
  OUTPUT_FILE=${RTOOL_HAPSET_RES}/${f}.rtool.out
  # location where epxected results are stored
  EXPECTED_FILE=${RTOOL_EXP_HAPSET}/${f}.rtool.out

  mkdir -p $RTOOL_HAPSET_RES || exit 1

  # we are chop off the first 3 lines (they contain the time the test was run).
  # We also need to add the time used in this step to the time to actually run the tests
  ($TIME java $DAIKON_CLASS "${RTOOL_OUT}/$f" | dos2unix >${OUTPUT_FILE}) 2>daikon.stderr.out
  remove_daik_header_footer $OUTPUT_FILE
  extract_time_and_add `tail -n 1 daikon.stderr.out`

  # next, check if the results match the expected
  echo "[DEBUG] Output file: ${OUTPUT_FILE}"
  echo "[DEBUG] Expected File: ${EXPECTED_FILE}"
  diff ${OUTPUT_FILE} $EXPECTED_FILE
  ret=$?

  if [ $ret -ne 0 ]
  then
    echo "$(tput setaf 1)Warning: Expected HaPSet results do not match$(tput sgr0)"
    echo "Test directory: $1"
  fi

done

# Count the number of invariants generated. This big sed command removes lines which are not invariants
#cat ${RTOOL_DPOR_RES}/*.out | sed '/===========================================================================/d' | sed '/.\+:::EXIT/d' | sed '/.\+:::ENTER/d' | sed '/Exiting Daikon\./d' | wc -l > ${RTOOL_DPOR_RES}/num_inv
count_inv ${RTOOL_HAPSET_RES}

# Save the total time to run over all the files
mv $TIME_OUTPUT ${RTOOL_HAPSET_RES}/ || exit 1
mv num_runs ${RTOOL_HAPSET_RES}/ || exit 1

# Finish HaPSet Test ============================================================

cleanup_between_tests

# Run daikon ==================================================================
# HaPSet is assumed to have run before this test. We extract the number of runs
# performed by HaPSet and run Daikon with the same number of runs
RUNS_FILE=${RTOOL_HAPSET_RES}/num_runs
if [ ! -f $RUNS_FILE ]
then
  echo "Error: HaPSet num runs file not found: $RUNS_FILE"
  echo "HaPSet must be run before daikon"
  exit 1
fi

DAIK_REPS=`cat $RUNS_FILE`

echo "Running Daikon on test $1"
echo "Num reps: $DAIK_REPS"

# Compile and run test
($TIME controller_ui.py daikon rep $DAIK_REPS) 2>kvas.stderr.out 1>kvas.stdout.out
# double check that any old time file is not around
rm -f $TIME_OUTPUT
extract_time_and_add `tail -n 1 kvas.stderr.out`

# Process results with daikon
mkdir -p $DAIK_RES || exit 1
OUTPUT_FILE=$DAIK_RES/daik.out

($TIME $JAVA daikon.Daikon $KVASIR_OUT >$OUTPUT_FILE) 2>daik.stderr.out
remove_daik_header_footer $OUTPUT_FILE
extract_time_and_add `tail -n 1 daik.stderr.out`

# count the number of invariants. This should be done before we move the time
# file since it also ends in .out!
count_inv $DAIK_RES
# move time file to results directory
mv $TIME_OUTPUT $DAIK_RES

# Finish daikon test ==========================================================

## Run DPOR on test ============================================================
#echo "Running DPOR on test $1"
## double check that any old time file is not around
#rm -f $TIME_OUTPUT
#($TIME controller_ui.py rtool comp) 2>comp.stderr.out
#extract_time_and_add `tail -n 1 comp.stderr.out`
## keep track of the time to run the test
#($TIME controller_ui.py rtool run 0 0 0) 2> dpor.stderr.out
## last line of stderr is the output of time
#extract_time_and_add `tail -n 1 dpor.stderr.out`
#
#
#TRACES=`ls $RTOOL_OUT`
#for f in $TRACES
#do
#  echo "Running on trace $f"
#  # location where RTool invariants will be stored
#  OUTPUT_FILE=${RTOOL_DPOR_RES}/${f}.rtool.out
#  # location where epxected results are stored
#  EXPECTED_FILE=${RTOOL_EXP_DPOR}/${f}.rtool.out
#
#  mkdir -p $RTOOL_DPOR_RES || exit 1
#
#  # we are chop off the first 3 lines (they contain the time the test was run).
#  # We also need to add the time used in this step to the time to actually run the tests
#  ($TIME java $DAIKON_CLASS "${RTOOL_OUT}/$f" | dos2unix >${OUTPUT_FILE}) 2>daikon.stderr.out
#  remove_daik_header_footer $OUTPUT_FILE
#  extract_time_and_add `tail -n 1 daikon.stderr.out`
#
#  # next, check if the results match the expected
#  echo "[DEBUG] Output file: ${OUTPUT_FILE}"
#  echo "[DEBUG] Expected File: ${EXPECTED_FILE}"
#  diff ${OUTPUT_FILE} $EXPECTED_FILE
#  ret=$?
#
#  if [ $ret -ne 0 ]
#  then
#    echo "$(tput setaf 1)Warning: Expected DPOR results do not match$(tput sgr0)"
#    echo "Test directory: $1"
#  fi
#
#done
#
## Count the number of invariants generated. This big sed command removes lines which are not invariants
##cat ${RTOOL_DPOR_RES}/*.out | sed '/===========================================================================/d' | sed '/.\+:::EXIT/d' | sed '/.\+:::ENTER/d' | sed '/Exiting Daikon\./d' | wc -l > ${RTOOL_DPOR_RES}/num_inv
#count_inv ${RTOOL_DPOR_RES}
#
## Save the total time to run over all the files
#mv $TIME_OUTPUT ${RTOOL_DPOR_RES}/
## Finish DPOR Test ============================================================


# Return to the parent directory.
cd ..
