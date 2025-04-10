#!/bin/bash

# Path to the plotter script (update if needed)
PLOTTER="common/plotter.py"

# Path to baseline CSV (constant)
BASELINE_CSV="../objective-a/task00/ssa-versions/ssa_blur_2x2_baseline.c.csv"

# Check that baseline exists
if [[ ! -f "$BASELINE_CSV" ]]; then
    echo "Baseline CSV not found at $BASELINE_CSV"
    exit 1
fi

# Activate virtual environment if needed
source venv/bin/activate 2>/dev/null || true

# Generate plot for each task
for t in task*/; do
    echo "Plotting CSVs in: $t"

    csvs=()
    for f in "$t"/*.csv; do
        [[ -f "$f" ]] && csvs+=("$f")
    done

    if [[ ${#csvs[@]} -eq 0 ]]; then
        echo "No CSVs found in $t — skipping."
        continue
    fi

    output="${t%/}.png"  # e.g., task00/ → task00.png

    python3 "$PLOTTER" "$output" "$BASELINE_CSV" "${csvs[@]}" --peak=9 --min=0
    echo "Plot saved to: $output"
done
