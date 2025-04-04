#!/bin/bash

for task in task*/; do
    echo "Running: tests for $(basename $task)..."
    bash $task/run-all-variant-tests.sh
done

echo "All tasks successfully tested for objective-$1."