echo "ENTER SWAP (Note: must be exact operation name; e.g. enter 'conv_4x3_ijqr')"
READ OP
echo "Note: this is for four interchanges, so the only swap is all 4 swaps."
SWAP="all"

python3 t03.py ssa-interchange-$OP-interchange_$SWAP.c $OP.operation interchange_$SWAP.txt