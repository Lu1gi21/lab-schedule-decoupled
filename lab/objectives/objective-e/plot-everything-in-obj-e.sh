#!/bin/bash

# Path to the plotter script relative to this file
PLOTTER="common/plotter.py"

# Output image file
OUTPUT="obj-e-all-plots.png"

# Activate virtual environment if available
source venv/bin/activate 2>/dev/null || true

# Collect all non-empty CSVs from within objective-e
csvs=()
while IFS= read -r -d '' file; do
    [[ -s "$file" ]] && csvs+=("$file")
done < <(find . -path './task*/*.csv' -type f -print0)

if [[ ${#csvs[@]} -eq 0 ]]; then
    echo "No non-empty CSV files found in objective-e."
    exit 1
fi

# Run the plotter on all collected CSVs
python3 "$PLOTTER" "$OUTPUT" "${csvs[@]}" --peak=3 --min=0

if [[ $? -eq 0 ]]; then
    echo "Plot generated: $OUTPUT"
else
    echo "Plotting failed."
fi
