#!/bin/bash

for variant in ./lab/objectives/objective-$1/task$2/var*; do
    echo "Running: cleaning $(basename $variant)..."
    bash $variant/run-clean-all.sh
done

echo "All variants cleaned for task $2 of objective $1."