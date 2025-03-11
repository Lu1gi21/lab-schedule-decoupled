#!/bin/bash

for task in ./lab/objectives/objective-$1/task*; do # Static path so it works regardless of where it is called
    echo "Running: measuring $(basename $task)..."
    bash $task/run-all-measure.sh
done

echo "All tasks successfully measured for objective-$1."