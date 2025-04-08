#!/bin/bash

for obj in objective-*/; do
    echo "Running: measuring $(basename $obj)..."
    bash $obj/run-all-measure.sh
done

