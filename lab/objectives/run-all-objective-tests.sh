#!/bin/bash

for obj in objective-*/; do
    echo "Running: tests for $(basename $obj)..."
    bash $obj/run-all-task-tests.sh
done
