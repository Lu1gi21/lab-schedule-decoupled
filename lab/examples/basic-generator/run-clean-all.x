#! /bin/bash
#
# Top level script to run verification in this directory.
# Note that the "-C" flag specifies the directory of the make file.

# NOTE: Adjust FILE_REF and FILE_TST to fit your task's needs.
#make -C ../.. clean-results FILE_REF=./examples/basic-generator/baseline.c FILE_TST=./examples/basic-generator/baseline.c
make -C ../.. clean-results FILE_REF=./examples/basic-generator/baseline.c FILE_TST=./examples/basic-generator/baseline.c

make -C ../.. clean-results FILE_REF=./examples/basic-generator/baseline.c FILE_TST=./examples/basic-generator/gen_var000.c

make -C ../.. clean-results FILE_REF=./examples/basic-generator/baseline.c FILE_TST=./examples/basic-generator/gen_var001.c

# NOTE: For every variant in the task (or test) make sure to run it in here if it is relevant.

# remove the coverage stuff
rm -rf htmlcov
rm -rf .coverage

#
rm -f gen_var000.c
rm -f gen_var001.c
