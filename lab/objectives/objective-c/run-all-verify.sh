#!/bin/bash

for task in ./lab/objectives/objective-$1/task*; do # Static path so it works regardless of where it is called
    echo "Running: verifying $(basename $task)..."
    bash $task/run-all-verify.sh
done

echo "All tasks successfully verified for objective-$1."