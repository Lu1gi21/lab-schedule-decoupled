#!/bin/bash 

echo "Running: cleaning all objectives..."
for obj in a b c d e; do
    echo "Running: cleaning objective $obj..."
    bash ./lab/objectives/objective-$obj/run-clean-all.sh
done

echo "All objectives successfully cleaned." 