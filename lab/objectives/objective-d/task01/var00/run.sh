echo "ENTER OPERATION (Note: must be exact operation name; e.g. enter 'conv_4x3_ijqr')"
read OP
echo "Note: this is for two unrolls, so the only swap is all 2 unrolls."
SCHEDULE=all

python3 var00.py ssa-unroll-$OP-unroll_$SCHEDULE.c $OP.operation unroll-$SCHEDULE.txt