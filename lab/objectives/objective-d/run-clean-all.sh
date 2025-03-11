#!/bin/bash

for task in ./lab/objectives/objective-$1/task*; do # Static path so it works regardless of where it is called
    echo "Running: cleaning $(basename $task)..."
    bash $task/run-clean-all.sh
done

echo "All tasks successfully cleaned for objective-$1."