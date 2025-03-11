#!/bin/bash

echo "Big Red Button has been activated!...standby..."
cd lab/objectives/
echo "Running all tests in each objective..."
bash ./run-all-objective-tests.sh
echo "Done running tests."