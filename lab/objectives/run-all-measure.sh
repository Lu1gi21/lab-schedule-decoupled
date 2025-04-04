#1/bin/bash

for obj in objective-*/; do
    echo "Running: measure for objective $obj..."
    bash ./$obj/run-all-measure.sh
done

echo "All objectives successfully measured."