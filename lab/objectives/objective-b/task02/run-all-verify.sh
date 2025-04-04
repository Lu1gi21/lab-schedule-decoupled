#!/bin/bash

for variant in var*/; do
    echo "Running: verifying $(basename $variant)..."
    # bash $variant/run-all-verify.sh
    make -C "$variant" measure-verifier
done

echo "All variants verified for task $2 of objective $1."