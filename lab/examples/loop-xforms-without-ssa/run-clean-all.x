#! /bin/bash
#
# Top level script to run verification in this directory.
# Note that the "-C" flag specifies the directory of the make file.

# NOTE: Adjust FILE_REF and FILE_TST to fit your task's needs.
make -C ../.. clean-results FILE_REF=./examples/loop-xforms-without-ssa/baseline.c FILE_TST=./examples/loop-xforms-without-ssa/baseline.c
make -C ../.. clean-results FILE_REF=./examples/loop-xforms-without-ssa/baseline.c FILE_TST=./examples/loop-xforms-without-ssa/unroll_var_q.c
make -C ../.. clean-results FILE_REF=./examples/loop-xforms-without-ssa/baseline.c FILE_TST=./examples/loop-xforms-without-ssa/unroll_var_r.c
make -C ../.. clean-results FILE_REF=./examples/loop-xforms-without-ssa/baseline.c FILE_TST=./examples/loop-xforms-without-ssa/interchange_var_ir.c
make -C ../.. clean-results FILE_REF=./examples/loop-xforms-without-ssa/baseline.c FILE_TST=./examples/loop-xforms-without-ssa/split_var_i_io_ii_4.c
make -C ../.. clean-results FILE_REF=./examples/loop-xforms-without-ssa/baseline.c FILE_TST=./examples/loop-xforms-without-ssa/cplx_var_split_i_io_ii_4_interchange_ii_j_unroll_r.c

# NOTE: For every variant in the task (or test) make sure to run it in here if it is relevant.
rm -f combined.png
