#!/bin/bash

for task in task*/; do
    echo "Running: verifying $(basename $task)..."
    bash $task/run-all-verify.sh
done

echo "All tasks successfully verified for objective-$1."