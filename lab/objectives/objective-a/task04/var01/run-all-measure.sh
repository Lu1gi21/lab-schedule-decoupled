#! /bin/bash
#
# Top level script to run verification and benchmarking in this directory.
# Note that the "-C" flag specifies the directory of the make file.

# Run measurement for var00
make -C var01 measure-all

# NOTE: Add more lines below if you have additional variants (e.g., var01, var02, etc.)
# make -C var01 measure-all
