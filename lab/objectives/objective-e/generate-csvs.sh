#!/bin/bash

for t in task*; do
    echo "Generating CSV files in: $(basename "$t")..."
    for f in $t/*.c; do
        make measure-performance FILE_TST=$(basename $f) TASK_DIR=$t
    done
done
