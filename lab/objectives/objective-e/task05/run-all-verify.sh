#!/bin/bash

for variant in ./lab/objectives/objective-$1/task$2/var*; do
    echo "Running: verifying $(basename $variant)..."
    bash $variant/run-all-verify.sh
done

echo "All variants verified for task $2 of objective $1."