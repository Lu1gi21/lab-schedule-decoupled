echo "ENTER OPERATION (Note: must be exact operation name; e.g. enter 'conv_4x3_ijqr')"
READ OP
echo "ENTER SWAP (Note: input using reverse lexographical order; e.g. to swap loops i0 and j0 enter 'ji')"
read SWAP

3 t08.py ssa-interchange-$OP-interchange_$SWAP.c $OP.operation interchange_$SWAP.txt
