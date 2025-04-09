#!/bin/bash

FULL=false
if [[ "$1" == "--full" ]]; then
    FULL=true
fi

cd ../task00
bash ./generate-all-baselines.sh
cd ../task04

for variant in var*/; do
    echo "Running: measuring $(basename "$variant")..."

    if $FULL; then
        make -C "$variant" measure-all
        make -C "$variant" plot-all  # <-- plot both baseline + variant
    else
        make -C "$variant" measure-verifier
        make -C "$variant" measure-performance
        make -C "$variant" plot-variant  # <-- just plot the variant
    fi
done