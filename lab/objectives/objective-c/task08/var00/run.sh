OP=conv_4x3_ijqr
echo "ENTER SWAP (Note: input using reverse lexographical order; e.g. to swap loops i0 and j0 enter 'ji')"
read SWAP

python3 t08.py ssa-interchange-$OP-interchange_$SWAP.c /$OP.operation interchange_$SWAP.txt