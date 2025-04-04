#!/bin/bash 

echo "Running: cleaning all objectives..."
for obj in objective-*/; do
    echo "Running: cleaning objective $obj..."
    bash ./$obj/run-clean-all.sh
done

echo "All objectives successfully cleaned." 