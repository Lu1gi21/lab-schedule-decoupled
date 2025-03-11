#!/bin/bash

echo "Running tests for Objective $1, Task $2, Variant $3..."
bash run-all-measure.sh
bash run-all-verify.sh
bash run-clean-all.sh
echo "Tests completed for Objective $1, Task $2, Variant $3."
