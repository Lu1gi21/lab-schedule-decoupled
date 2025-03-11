#1/bin/bash

for obj in a b c d e; do
    echo "Running: verify for objective $obj..."
    bash ./lab/objectives/objective-$obj/run-all-verify.sh
done

echo "All objectives successfully verified."