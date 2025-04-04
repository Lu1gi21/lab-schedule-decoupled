#!/bin/bash

for obj in objective-*/; do
    echo "Running: verifying $(basename $obj)..."
    bash $obj/run-all-verify.sh
done
