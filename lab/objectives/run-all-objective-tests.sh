#!/bin/bash

for obj in objective-*/; do
    echo "Running: tests for $(basename "$obj")..."
    (
        cd "$obj" || exit
        bash ./run-all-task-tests.sh
    )
done
