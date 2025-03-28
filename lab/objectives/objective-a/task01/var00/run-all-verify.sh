#! /bin/bash
#
# Top level script to run verification in this directory.
# Note that the "-C" flag specifies the directory of the make file.

# NOTE: Adjust FILE_REF and FILE_TST to fit your task's needs.
#make -C ../.. measure-verifier FILE_REF=./examples/basic/baseline.c FILE_TST=./examples/basic/baseline.c
make -C ../.. measure-verifier FILE_REF=./examples/basic/baseline.c FILE_TST=./examples/basic/test_var000.c

# NOTE: For every variant in the task (or test) make sure to run it in here if it is relevant.
