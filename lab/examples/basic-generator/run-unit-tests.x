#! /bin/bash
#
# https://coverage.readthedocs.io/en/7.6.12/

. ../../venv/bin/activate

# all the tests comined (-a --append) should give us 100% on the code we wrote.
coverage run -a ./generator-baseline.py gen_var000.c
coverage run -a ./generator-baseline.py gen_var000.c blah blah

# NOTE: The compiler is not covered well.
coverage run -a ./generator-structured.py gen_var000.c
coverage run -a ./generator-structured.py gen_var000.c blah blah

coverage report -m
coverage html
