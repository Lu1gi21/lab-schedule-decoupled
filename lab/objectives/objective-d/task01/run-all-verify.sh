#!/bin/bash

for variant in var*/; do
    echo "Running: verifying $(basename $variant)..."
    # bash $variant/run-all-verify.sh
    make -C "$variant" measure-verifier
done
