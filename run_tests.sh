#!/bin/bash

# Run all the tests


TESTS="AccountBad \
DekkerSafe \
FibBenchSafe
IncCas \
IncDec \
IncDecCas
IncTrue \
LamportSafe \
LogProcSweep \
PetersonSafe
Reorder \
Stateful01_Safe \
Sync01_Safe \
Szymanski \
TimeVarMutexSafe \
Lazy01Safe \
nbds-hashtable \
LogProcSweep"

# check to make sure each directory actually exists
for f in $TESTS
do
  if [ ! -d $f ]
  then
    echo "Error: Directory not found: $f"
  fi
done


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

