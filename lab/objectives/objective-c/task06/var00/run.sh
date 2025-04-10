echo "ENTER OPERATION (Note: must be exact operation name; e.g. enter 'conv_4x3_ijqr')"
read OP
echo "ENTER UNROLL (Note: input loop to be unrolled; e.g. 'r0' to unroll loop r0)"
read SCHEDULE

python3 var00.py ssa-unroll-$OP-unroll_$SCHEDULE.c $OP.operation unroll-$SCHEDULE.txt