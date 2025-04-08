#!/bin/bash

for task in task*/; do
    echo "Running: cleaning $(basename $task)..."
    bash $task/run-clean-all.sh
done
