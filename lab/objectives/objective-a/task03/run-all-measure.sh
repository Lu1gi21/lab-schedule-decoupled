#!/bin/bash

for variant in ./lab/objectives/objective-$1/task$2/var*; do
    echo "Running: measuring $(basename $variant)..."
    bash $variant/run-all-measure.sh
done

echo "All variants measured for task $2 of objective $1."