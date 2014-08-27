#!/bin/bash

# Run all the tests


TESTS="AccountBad LogProcSweep Szymanski Reorder Lazy01Safe LogProcSweep IncCas IncDec IncTrue IncDecCas"

# secret feature: pass clean as argument one to delete all the output files
if [ "$1" = "clean" ]
then
  for t in $TESTS 
  do
    cd $t
    controller_ui.py rtool clean
    cd ..
  done
  exit 0
fi

for t in $TESTS 
do
  echo "Running R_Tool test: $t"
  ./run.sh $t || exit 1
  echo "Finished test: $t"
done

