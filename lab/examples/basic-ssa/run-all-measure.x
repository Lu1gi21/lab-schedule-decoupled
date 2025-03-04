#! /bin/bash
#
# Top level script to run verification in this directory.
# Note that the "-C" flag specifies the directory of the make file.

# NOTE: Adjust FILE_REF and FILE_TST to fit your task's needs.
#make -C ../.. measure-all FILE_REF=./examples/basic-ssa/baseline.c FILE_TST=./examples/basic-ssa/baseline.c
make -C ../.. measure-all FILE_REF=./examples/basic-ssa/baseline.c FILE_TST=./examples/basic-ssa/baseline.c
make -C ../.. measure-all FILE_REF=./examples/basic-ssa/baseline.c FILE_TST=./examples/basic-ssa/ssa_var000.c
make -C ../.. measure-all FILE_REF=./examples/basic-ssa/baseline.c FILE_TST=./examples/basic-ssa/ssa_var001.c
# NOTE: For every variant in the task (or test) make sure to run it in here if it is relevant.


. ../../venv/bin/activate; ls *.c.csv | xargs ../../plotter.py combined.png


