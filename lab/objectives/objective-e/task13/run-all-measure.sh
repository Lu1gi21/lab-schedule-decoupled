#!/bin/bash

for task in task*/; do 
    echo "Running: measuring $(basename $task)..."
    bash $task/run-all-measure.sh
done

echo "All tasks successfully measured for objective-$1."