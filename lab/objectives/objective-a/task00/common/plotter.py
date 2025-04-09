#!/usr/bin/env python3

import sys
import pandas as pd
from matplotlib import pyplot as plt

# Default y-axis limits
y_min = 0.0
y_max = 3.0  # Default fallback for peak

file_names  = []
output_file = None

# Parse command-line arguments
for arg in sys.argv[1:]:
    if arg.startswith("--peak="):
        try:
            y_max = float(arg.split("=", 1)[1])
        except ValueError:
            print("Warning: Invalid --peak value, using default")
    elif arg.startswith("--min="):
        try:
            y_min = float(arg.split("=", 1)[1])
        except ValueError:
            print("Warning: Invalid --min value, using default")
    elif output_file is None:
        output_file = arg
    else:
        file_names.append(arg)

if not output_file or not file_names:
    print("Usage: ./plotter.py output.png file1.csv [file2.csv ...] [--peak=X] [--min=Y]")
    sys.exit(1)

# Plotting logic
for fn in file_names:
    df = pd.read_csv(fn)
    plt.plot(df['size'], df['throughput'], label=fn)

plt.legend(loc="upper right")
plt.ylim(y_min, y_max)
plt.xlim(0, None)
plt.title("Performance Versus Problem Size")
plt.xlabel("Problem Size")
plt.ylabel("Performance (GFLOP/s)")
plt.savefig(output_file)
