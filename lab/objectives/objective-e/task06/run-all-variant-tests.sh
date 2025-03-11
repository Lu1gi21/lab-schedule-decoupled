#!/bin/bash

for variant in ./lab/objectives/objective-$1/task$2/var*; do
    echo "Running: tests for $(basename $variant)..."
    bash $variant/run-all-tests.sh
done

echo "All variants tested for task $2 of objective $1."