#!/bin/bash

for obj in objective-*/; do
    echo "Running: cleaning $(basename $obj)..."
    bash $obj/run-clean-all.sh
done
