#!/bin/bash

for task in task*/; do
    echo "Cleaning task: $(basename "$task")"
    for cfile in "$task"/*.c; do
        [ -e "$cfile" ] || continue  # skip if no .c files
        make clean-results FILE_TST=$(basename "$cfile") TASK_DIR=$task
    done
done
