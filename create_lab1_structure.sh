#!/bin/bash

mkdir -p ./lab
touch big-red-button.sh
mkdir ./lab/docs/
mkdir ./lab/utils/ # any additional tooling and code that provide support
mkdir ./lab/objectives/
touch ./lab/objectives/{run-all-verify.sh,run-all-measure.sh,run-clean-all.sh} # scripts to run/clean/bench everything

declare -A task_counts=(
    ["a"]=5    # Objective A has 5 tasks (00-04)
    ["b"]=4    # Objective B has 4 tasks (00-03)
    ["c"]=9    # Objective C has 9 tasks (00-08)
    ["d"]=7    # Objective D has 7 tasks (00-06)
    ["e"]=14   # Objective E has 14 tasks (00-13)
)

for obj in a b c d e; do
    mkdir -p ./lab/objectives/objective-$obj
    touch ./lab/objectives/objective-$obj/{run-all-task-tests.sh,run-all-verify.sh,run-all-measure.sh,run-clean-all.sh}

    for task_num in $(seq -w 0 $((task_counts[$obj]-1))); do
        task=$(printf "task%02d" $((10#$task_num)))  # Format task number as "task00" to keep convention across variants
        mkdir -p ./lab/objectives/objective-$obj/$task
        touch ./lab/objectives/objective-$obj/$task/{run-all-variant-tests.sh,run-all-verify.sh,run-all-measure.sh,run-clean-all.sh}

        for var in 00 01; do
            mkdir -p ./lab/objectives/objective-$obj/$task/var$var
            touch ./lab/objectives/objective-$obj/$task/var$var/{run-all-tests.sh,run-all-verify.sh,run-all-measure.sh,run-clean-all.sh}
        done
    done
done

touch ./lab/objectives/objective-{b,c,d}/run-unit-tests.sh # run unit tests and coverage on all of the generators (use ./lab/examples/basic-generator for ideas on unit testing and coverage)

for obj in b c d; do
    mkdir -p ./lab/objectives/objective-$obj/unit-tests/{input,expected-output,tests}
    touch ./lab/objectives/objective-$obj/unit-tests/input/input00.txt
    touch ./lab/objectives/objective-$obj/unit-tests/expected-output/output00.out
    touch ./lab/objectives/objective-$obj/unit-tests/tests/task00-var00-test00.x
done