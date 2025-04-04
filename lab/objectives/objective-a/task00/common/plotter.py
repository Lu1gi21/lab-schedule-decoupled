#!/usr/bin/env python3
#
# modify as you see fit.
#
# This script was written for red hat based systems, so
# depending on your system you may need to install
# matplotlip and pandas "pip install matplotlib --user"
# You may also want to use virtual environments
#
#
# Usage
#
# ./plotter.py plotname.png perf1.csv [perf2.csv perf3.csv ....]
#
# This will create a png of all of the performance results.


#!/usr/bin/env python3

import sys
import pandas as pd
from matplotlib import pyplot as plt

# Usage: ./plotter.py output.png file1.csv [file2.csv ...] [--peak=X]
file_names  = []
output_file = None
machine_gflop_peak = 3.0  # default fallback

# Parse command-line arguments
for arg in sys.argv[1:]:
    if arg.startswith("--peak="):
        try:
            machine_gflop_peak = float(arg.split("=", 1)[1])
        except ValueError:
            print("Warning: Invalid --peak value, using default")
    elif output_file is None:
        output_file = arg
    else:
        file_names.append(arg)

if not output_file or not file_names:
    print("Usage: ./plotter.py output.png file1.csv [file2.csv ...] [--peak=X]")
    sys.exit(1)

# Plotting logic
for fn in file_names:
    df = pd.read_csv(fn)
    plt.plot(df['size'], df['throughput'], label=fn)

plt.legend(loc="upper right")
plt.ylim(0, machine_gflop_peak)
plt.xlim(0, None)
plt.title("Performance Versus Problem Size")
plt.xlabel("Problem Size")
plt.ylabel("Performance (GFLOP/s)")
plt.savefig(output_file)
