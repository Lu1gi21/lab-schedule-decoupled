#!/bin/bash

FULL=false
if [[ "$1" == "--full" ]]; then
    FULL=true
fi

# Ensure baseline results are up to date
echo "Generating all baseline results..."
cd ../../objective-a/task00/ssa-versions/
bash ./generate-all-baselines.sh
cd ../../../objective-e/

# Loop over task folders
for task in task*/; do
    echo "Entering: $task"

    for cfile in "$task"/*.c; do
        [ -e "$cfile" ] || continue
        file_name=$(basename "$cfile")

        echo "  Measuring: $file_name in $(basename "$task")"

        if $FULL; then
            make measure-all FILE_TST="$file_name" TASK_DIR="$task"
            make plot-all FILE_TST="$file_name" TASK_DIR="$task"
        else
            make measure-verifier FILE_TST="$file_name" TASK_DIR="$task"
            make measure-performance FILE_TST="$file_name" TASK_DIR="$task"
            make plot-variant FILE_TST="$file_name" TASK_DIR="$task"
        fi
    done
done
