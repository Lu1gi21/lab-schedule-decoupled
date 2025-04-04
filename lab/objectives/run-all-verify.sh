#1/bin/bash

for obj in objective-*/; do
    echo "Running: verify for objective $obj..."
    bash ./$obj/run-all-verify.sh
done

echo "All objectives successfully verified."