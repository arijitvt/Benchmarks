#!/bin/bash

# error when using undefined variables
set -u
# exit on command error
#set -e 

# Automatic test runner. Beware! This thing is ugly.
# If a directory contains a file named `no_dpor` the dpor test will be skipped.

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
# Directory holding expected HaPSet results
RTOOL_EXP_HAPSET=rtool_exp_hapset

# Directory to hold invariants learned by RTool using PCB 2
RTOOL_PCB_RES=rtool_res_pcb
# Directory holding expected PCB results
RTOOL_EXP_PCB=rtool_exp_pcb

# This string should match all the kvasir output files
KVASIR_OUT="arijit/output_*"

# Directory to hold output of kvasir+daikon
DAIK_RES=daik_res

# location where extract_time() saves time output 
TIME_OUTPUT=time.out

# Command use to time tests. Currently, this is the elapsed real time in seconds. The tests are limited to one hour.
TIME="`which time` -f %e"


PCB_RUNS_FILE=${RTOOL_PCB_RES}/num_runs
HAPSET_RUNS_FILE=${RTOOL_HAPSET_RES}/num_runs
DPOR_RUNS_FILE=${RTOOL_DPOR_RES}/num_runs

# Location to dump stderr/stdout of different tests
DPOR_STDOUT="dpor.stdout.out"
DPOR_STDERR="dpor.stderr.out"
PCB_STDERR="pcb.stderr.out"
PCB_STDOUT="pcb.stdout.out"
# hapset is hardcoded

# If this file exists, DPOR will be skiped
NO_DPOR_FILE="no_dpor"

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
  CUR_TIME=`cat $TIME_OUTPUT`
  echo "$1 + $CUR_TIME" | bc > $TIME_OUTPUT || exit 1
  echo "New Time: " 
  cat $TIME_OUTPUT
}

# This should be called between each individual test (e.g., between DPOR and
# HaPSet
cleanup_between_tests() {
  rm -rf arijit/
  rm -f time.out
  rm -f hook.*
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
  if [ -z ${1+x} ] 
  then
    echo "Error: count_num_runs() must be passed a file as argument one"
    exit 1
  fi
  grep 'Total number of runs: ' "$1" | cut -d':' -f2 | cut -c 2- >num_runs
}

# $1 should be a directory to test

if [ -z ${1+x} ]
then
  echo "Error: Please pass directory to test as first argument"
  exit 1
fi


cd $1 || exit 1

# clean up old results
controller_ui.py rtool clean
# rebiuild
controller_ui.py rtool comp

# Run HaPSet on test ============================================================
echo "Running HaPSet on test $1"
# double check that any old time file is not around
rm -f $TIME_OUTPUT
#($TIME controller_ui.py rtool comp) 2>comp.stderr.out
#extract_time_and_add `tail -n 1 comp.stderr.out`
# keep track of the time to run the test
date
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

# Run PCB 2 on test ============================================================
echo "Running PCB on test $1"
# double check that any old time file is not around
rm -f $TIME_OUTPUT
#($TIME controller_ui.py rtool comp) 2>comp.stderr.out
#extract_time_and_add `tail -n 1 comp.stderr.out`
# keep track of the time to run the test
date
($TIME controller_ui.py rtool run 0 1 2) 2> $PCB_STDERR 1>$PCB_STDOUT
echo "Time Return: $?"
# last line of stderr is the output of time
extract_time_and_add `tail -n 1 $PCB_STDERR`
count_num_runs "$PCB_STDOUT"

TRACES=`ls $RTOOL_OUT`
for f in $TRACES
do
  echo "Running on trace $f"
  # location where RTool invariants will be stored
  OUTPUT_FILE=${RTOOL_PCB_RES}/${f}.rtool.out
  # location where epxected results are stored
  EXPECTED_FILE=${RTOOL_EXP_PCB}/${f}.rtool.out

  mkdir -p $RTOOL_PCB_RES || exit 1

  # we are chop off the first 3 lines (they contain the time the test was run).
  # We also need to add the time used in this step to the time to actually run the tests
  ($TIME java $DAIKON_CLASS "${RTOOL_OUT}/$f" | dos2unix >${OUTPUT_FILE}) 2>daikon.stderr.out
  echo "Time Return: $?"
  remove_daik_header_footer $OUTPUT_FILE
  extract_time_and_add `tail -n 1 daikon.stderr.out`

  # next, check if the results match the expected
  echo "[DEBUG] Output file: ${OUTPUT_FILE}"
  echo "[DEBUG] Expected File: ${EXPECTED_FILE}"
  diff ${OUTPUT_FILE} $EXPECTED_FILE
  ret=$?

  if [ $ret -ne 0 ]
  then
    echo "$(tput setaf 1)Warning: Expected PCB results do not match$(tput sgr0)"
    echo "Test directory: $1"
  fi

done

# Count the number of invariants generated. This big sed command removes lines which are not invariants
#cat ${RTOOL_DPOR_RES}/*.out | sed '/===========================================================================/d' | sed '/.\+:::EXIT/d' | sed '/.\+:::ENTER/d' | sed '/Exiting Daikon\./d' | wc -l > ${RTOOL_DPOR_RES}/num_inv
count_inv ${RTOOL_PCB_RES}

# Save the total time to run over all the files
mv $TIME_OUTPUT ${RTOOL_PCB_RES}/ || exit 1
mv num_runs ${RTOOL_PCB_RES}/ || exit 1
# Finish PCB 2 Test ============================================================

cleanup_between_tests

# Run DPOR on test ============================================================
echo "Running DPOR on test $1"

if [ -f "$NO_DPOR_FILE" ]
then
  echo "Skipping DPOR"
else 
  # double check that any old time file is not around
  rm -f $TIME_OUTPUT
  date
  ($TIME controller_ui.py rtool comp) 2>comp.stderr.out
  extract_time_and_add `tail -n 1 comp.stderr.out`
  # keep track of the time to run the test
  ($TIME controller_ui.py rtool run 0 0 0) 2> $DPOR_STDERR 1>$DPOR_STDOUT
  echo "Time Return: $?"
  # last line of stderr is the output of time
  extract_time_and_add `tail -n 1 $DPOR_STDERR`
  count_num_runs "$DPOR_STDOUT"


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
    ($TIME java $DAIKON_CLASS "${RTOOL_OUT}/$f" | dos2unix >${OUTPUT_FILE}) 2>daikon.stderr.out
    echo "Time Return: $?"
    remove_daik_header_footer $OUTPUT_FILE
    extract_time_and_add `tail -n 1 daikon.stderr.out`

    # next, check if the results match the expected
    echo "[DEBUG] Output file: ${OUTPUT_FILE}"
    echo "[DEBUG] Expected File: ${EXPECTED_FILE}"
    diff ${OUTPUT_FILE} $EXPECTED_FILE
    ret=$?

    if [ $ret -ne 0 ]
    then
      echo "$(tput setaf 1)Warning: Expected DPOR results do not match$(tput sgr0)"
      echo "Test directory: $1"
    fi

  done

  # Count the number of invariants generated. This big sed command removes lines which are not invariants
  #cat ${RTOOL_DPOR_RES}/*.out | sed '/===========================================================================/d' | sed '/.\+:::EXIT/d' | sed '/.\+:::ENTER/d' | sed '/Exiting Daikon\./d' | wc -l > ${RTOOL_DPOR_RES}/num_inv
  count_inv ${RTOOL_DPOR_RES}

  # Save the total time to run over all the files
  mv $TIME_OUTPUT ${RTOOL_DPOR_RES}/ || exit 1
  mv num_runs ${RTOOL_DPOR_RES}/ || exit 1
fi
# Finish DPOR Test ============================================================

cleanup_between_tests

# Run daikon ==================================================================
# HaPSet/DPOR is assumed to have run before this test. We extract the number of
# runs performed by HaPSet/DPOR/PCB and run Daikon with the same number of runs
# as the max. 

# DAIK_NUM_RUNS is set to look at DPOR. But, for some tests we skip DPOR. When this happens, choose the max of PCB and HaPSet
#if [ -f "$NO_DPOR_FILE" ]
#then
#  PCB_NUM_RUNS=`cat $PCB_RUNS_FILE`
#  HAPSET_NUM_RUNS=`cat $HAPSET_RUNS_FILE`
#  echo "[DEBUG] PCB Runs: $PCB_NUM_RUNS"
#  echo "[DEBUG] HaPSet Runs: $HAPSET_NUM_RUNS"
#  # Calculate the max of the number of runs PCB and HaPSet. 
#  if [ $PCB_NUM_RUNS -gt $HAPSET_NUM_RUNS ]
#  then
#    RUNS_FILE=$PCB_RUNS_FILE
#  else
#    RUNS_FILE=$HAPSET_RUNS_FILE
#  fi
#else
#  RUNS_FILE=$DAIK_NUM_RUNS
#fi

# Calculate the maximum of the number of runs of the test performed previously
#if [ -f "$PCB_RUNS_FILE" ]
#then
#  PCB_NUM_RUNS=`cat $PCB_RUNS_FILE`
#else
#  PCB_NUM_RUNS="0"
#fi
#
#if [ -f "$HAPSET_RUNS_FILE" ]
#then
#  HAPSET_NUM_RUNS=`cat $HAPSET_RUNS_FILE`
#else
#  HAPSET_NUM_RUNS="0"
#fi
#
#if [ -f "$DPOR_RUNS_FILE" ]
#then
#  DPOR_NUM_RUNS=`cat $DPOR_RUNS_FILE`
#else
#  DPOR_NUM_RUNS="0"
#fi

# use sort to find the max of the number of runs
#DAIK_REPS=`echo "$PCB_NUM_RUNS $HAPSET_NUM_RUNS $DPOR_NUM_RUNS" | tr ' ' '\n' | sort -nr | head -n 1`
DAIK_REPS=`cat $HAPSET_RUNS_FILE`

#if [ ! -f $RUNS_FILE ]
#then
#  echo "Error: num_runs file not found: $RUNS_FILE"
#  echo "HaPSet must be run before daikon"
#  exit 1
#fi
#
#DAIK_REPS=`cat $RUNS_FILE`

echo "Running Daikon on test $1"
echo "Num reps: $DAIK_REPS"

# Compile and run test
date
($TIME controller_ui.py daikon rep $DAIK_REPS) 2>kvas.stderr.out 1>kvas.stdout.out
echo "Time Return: $?"
# double check that any old time file is not around
rm -f $TIME_OUTPUT
extract_time_and_add `tail -n 1 kvas.stderr.out`

# Process results with daikon
mkdir -p $DAIK_RES || exit 1
OUTPUT_FILE=$DAIK_RES/daik.out

($TIME $JAVA daikon.Daikon $KVASIR_OUT >$OUTPUT_FILE) 2>daik.stderr.out
echo "Time Return: $?"
remove_daik_header_footer $OUTPUT_FILE
extract_time_and_add `tail -n 1 daik.stderr.out`

# count the number of invariants. This should be done before we move the time
# file since it also ends in .out!
count_inv $DAIK_RES
# move time file to results directory
mv $TIME_OUTPUT $DAIK_RES || exit 1
echo "$DAIK_REPS" >$DAIK_RES/num_runs || exit 1

# Finish daikon test ==========================================================


# Return to the parent directory.
cd ..
