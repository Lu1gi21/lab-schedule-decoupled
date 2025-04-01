OP=blur_4x4_ijqr
echo "ENTER SWAP (Note: input using reverse lexographical order; e.g. to swap loops i0 and j0 enter 'ji')"
read SWAP

python3 ssa_interchange_$OP.py ssa-interchange-$OP-interchange_$SWAP.c ../operations/$OP.operation ../interchanges/interchange_$SWAP.txt