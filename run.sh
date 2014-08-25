#!/bin/bash

# Directory holding output dtrace files to be processed by daikon
RTOOL_OUT=arijit

# Name of the class where daikon's main file is
DAIKON_CLASS=daikon.Daikon

# JVM to use
JAVA=java

# Directory to hold invariants learned by RTool
RTOOL_RESULTS=rtool_res

# Directory holding expected DPOR results
RTOOL_EXP_DPOR=rtool_exp_dpor

# $1 should be a directory to test

if [ -z "$1" ]
then
  echo "Error: Please pass directory to test as first argument"
  exit 1
fi


cd $1 || exit 1
controller_ui.py rtool comp || exit 1
controller_ui.py rtool run 0 0 0 || exit 1
TRACES=`ls $RTOOL_OUT`
for f in $TRACES
do
  echo "Running on trace $f"
  # location where RTool invariants will be stored
  OUTPUT_FILE=${RTOOL_RESULTS}/${f}.rtool.out
  # location where epxected results are stored
  EXPECTED_FILE=${RTOOL_EXP_DPOR}/${f}.rtool.out

  mkdir -p $RTOOL_RESULTS || exit 1

  # we are chop off the first 3 lines (they contain the time)
  java $DAIKON_CLASS "${RTOOL_OUT}/$f" | sed -e '1,3d' > ${OUTPUT_FILE}

  # next, check if the results match the expected
  diff ${OUTPUT_FILE} $EXPECTED_FILE
  ret=$?

  if [ $ret -ne 0 ]
  then
    echo "$(tput setaf 1)Warning: Expected results do not match$(tput sgr0)"
    #echo "Warning: Expected results do not match"
  fi

done
cd ..
