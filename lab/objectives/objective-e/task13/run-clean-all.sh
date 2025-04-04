#!/bin/bash

for task in task*/; do
    echo "Running: cleaning $(basename $task)..."
    bash $task/run-clean-all.sh
done

echo "All tasks successfully cleaned for objective-$1."