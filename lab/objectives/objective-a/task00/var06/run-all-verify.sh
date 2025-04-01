#! /bin/bash
#
# Top level script to run verification in this directory.
# Note that the "-C" flag specifies the directory of the make file.

# Hardcoded file name to verify in this variant
FILE_TST=ssa-jacobi2d_5pt_ijqr_var06.c
FILE_REF=../ssa-versions/ssa_baseline.c

make -C ../.. measure-verifier FILE_REF="$FILE_REF" FILE_TST="$FILE_TST"

# NOTE: For every variant in the task (or test) make sure to run it in here if it is relevant.