#!/bin/bash

for variant in var*/; do
    echo "Running: cleaning $(basename $variant)..."
    make -C "$variant" clean-all
done
