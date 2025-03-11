#1/bin/bash

for obj in a b c d e; do
    echo "Running: measure for objective $obj..."
    bash ./lab/objectives/objective-$obj/run-all-measure.sh
done

echo "All objectives successfully measured."