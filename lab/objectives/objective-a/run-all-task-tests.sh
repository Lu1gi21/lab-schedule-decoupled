#!/bin/bash

for task in task*/; do
    echo "Running: tests for $(basename "$task")..."
    (
        cd "$task" || exit
        bash ./run-all-variant-tests.sh
    )
done
