#!/bin/bash

for task in ./lab/objectives/objective-a/task*; do # Static path so it works regardless of where it is called
    echo "Running: tests for $(basename $task)..."
    bash $task/run-all-variant-tests.sh
done

echo "All tasks successfully tested for objective-a."