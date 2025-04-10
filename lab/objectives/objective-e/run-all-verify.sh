#!/bin/bash

for task in task*/; do
    echo "Verifying task: $(basename "$task")"
    for cfile in "$task"/*.c; do
        [ -e "$cfile" ] || continue
        echo " - Verifying: $cfile"
        make measure-verifier FILE_TST=$(basename "$cfile") TASK_DIR=$task
    done
done
