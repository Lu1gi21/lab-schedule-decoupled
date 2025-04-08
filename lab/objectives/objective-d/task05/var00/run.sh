echo "ENTER OPERATION (Note: must be exact operation name; e.g. enter 'conv_4x3_ijqr')"
READ OP
echo "Note: this is for 2 interchanges and 2 splits. Used example is split_ijqr_2_interchange_qirj."
SCHEDULE="split_ijqr_2_interchange_qirj"

python3 t05.py ssa-interchange-$OP-$SCHEDULE.c $OP.operation $SCHEDULE.txt