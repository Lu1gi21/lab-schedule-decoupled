#!/bin/bash

mkdir -p ./lab
touch big-red-button.sh
mkdir ./lab/docs/
mkdir ./lab/utils/ # any additional tooling and code that provide support
mkdir ./lab/objectives/
touch ./lab/objectives/{run-all-objective-tests.sh,run-all-verify.sh,run-all-measure.sh,run-clean-all.sh} # scripts to run/clean/bench everything

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

    for task in $(seq -w 0 $((task_counts[$obj]-1))); do
        mkdir -p ./lab/objectives/objective-$obj/task$task
        touch ./lab/objectives/objective-$obj/task$task/{run-all-variant-tests.sh,run-all-verify.sh,run-all-measure.sh,run-clean-all.sh}

        for var in 00 01; do
            mkdir -p ./lab/objectives/objective-$obj/task${task}/var${var}
            touch ./lab/objectives/objective-$obj/task${task}/var${var}/{run-all-tests.sh,run-all-verify.sh,run-all-measure.sh,run-clean-all.sh}
        done
    done
done

touch ./lab/objectives/objective-{b,c,d}/run-unit-tests.sh # run unit tests and coverage on all of the generators (use ./lab/examples/basic-generator for ideas on unit testing and coverage)

