#1/bin/bash

echo "For all objectives:\n"

for obj in a b c d e; do
    echo "Running: tests for objective $obj..."
    bash ./lab/objectives/objective-$obj/run-all-task-tests.sh
done

echo "All objectives successfully tested."



# echo "Running: Measure..."
# bash ./run-all-measure.sh

# echo "Running: Verify..."
# bash ./run-all-verify.sh

# echo "Running: Clean..."
# bash ./run-clean-all.sh

