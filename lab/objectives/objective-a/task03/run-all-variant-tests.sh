#!/bin/bash
bash ./interchange-versions/generate-all-interchanges.sh
bash ./run-clean-all.sh
bash ./run-all-verify.sh
bash ./run-all-measure.sh  --full