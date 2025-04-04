#!/bin/bash

for variant in var*/; do
    echo "Running: cleaning $(basename $variant)..."
    make -C "$variant" clean-all
done

echo "All variants cleaned for task $2 of objective $1."