# This file is responsible for building the program
# Modify the "FILE_TST" to reference the filename
# that you want to test.
#
# To build the code
#


# you can set this variable on the command line
# make all FILE_TST=test_varXXX.c
# make all FILE_REF=baseline.c
# make all CFLAGS="-O3"
# make all FILE_TST=test_varXXX.c  FILE_REF=baseline.c CFLAGS="-O3"

# This line may need to be updated to match your file in case I missed it...
FILE_TST?=../interchange-versions/ssa-interchange-conv_4x3_ijqr_interchange_rq.c
# Update the line below accordingly
FILE_REF?=../../task00/ssa-versions/ssa_conv_4x3_baseline.c


OSACA_DOT_FILE_TST="$(FILE_TST).osaca.dot"
# NOTE: requires graphviz to be installed locally
# https://pygraphviz.github.io/documentation/stable/install.html
# install graphiz locally and add pygraphviz to requirements.txt
#OSACA_FLAGS?=--export-graph $(OSACA_DOT_FILE_TST)
OSACA_FLAGS?=


ASM_FILE_TST="$(FILE_TST).s"
ASM_FILE_REF="$(FILE_REF).ref.s"
OBJ_FILE_TST="$(FILE_TST).o"
OBJ_FILE_REF="$(FILE_REF).ref.o"
OBJ_FILE_DBG_TST="$(FILE_TST).dbg.o"

OBJDUMP_FILE_TST="$(FILE_TST).objdump"
OBJDUMP_ANNOTATED_FILE_TST="$(FILE_TST).annotated.objdump"
OSACA_ASM_FILE_TST="$(FILE_TST).osaca.s"
OSACA_FILE_TST="$(FILE_TST).osaca"



MCA_ASM_FILE_TST="$(FILE_TST).mca.s"
MCA_FILE_TST="$(FILE_TST).mca"
CACHEGRIND_FILE_TST="$(FILE_TST).cachegrind.out"

RES_CSV_FILE_TST=$(FILE_TST).res.csv
CSV_FILE_TST="$(FILE_TST).csv"
PNG_FILE_TST="$(FILE_TST).png"

#####

CFLAGS?=-std=c99 -O2 -mavx2 -mfma -fopenmp -I./ # Feel free to modify the optimization flags, but the impact will be marginal at best.
CFLAGS_DEBUG=${CFLAGS} -g
#CFLAGS_DEBUG=-std=c99 -g -O0 -fopenmp # If you modify this you really shouldn't muck with the optimization flags.
#####
NAME_REF=compute_ref # leave this alone
NAME_TST=compute_tst # also leave this alone
NAME_FLOP_REF=compute_flop_ref # leave this alone
NAME_FLOP_TST=compute_flop_tst # also leave this alone
NAME_BYTES_REF=compute_bytes_ref # leave this alone
NAME_BYTES_TST=compute_bytes_tst # also leave this alone





all: build-verifier build-timer


build-verifier:
	gcc $(CFLAGS_DEBUG) -DCOMPUTE_NAME_REF=$(NAME_REF)  -DCOMPUTE_NAME_TST=$(NAME_TST) -DCOMPUTE_FLOP_NAME_REF=$(NAME_FLOP_REF)  -DCOMPUTE_FLOP_NAME_TST=$(NAME_FLOP_TST) -c ../common/verifier.c -o verifier.o
	gcc $(CFLAGS_DEBUG) -DCOMPUTE_NAME=$(NAME_REF) -DCOMPUTE_FLOP_NAME=$(NAME_FLOP_REF) -DCOMPUTE_BYTES_NAME=$(NAME_BYTES_REF) -c $(FILE_REF) -o $(OBJ_FILE_REF)
	gcc $(CFLAGS_DEBUG) -DCOMPUTE_NAME=$(NAME_TST) -DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) -DCOMPUTE_BYTES_NAME=$(NAME_BYTES_TST) -c $(FILE_TST) -o $(OBJ_FILE_TST)
	gcc $(CFLAGS_DEBUG) -lm $(OBJ_FILE_REF) $(OBJ_FILE_TST) verifier.o -o ./run_verifier.x


build-timer-infrastructure: ../common/timer.c
	gcc $(CFLAGS) -DCOMPUTE_NAME_TST=$(NAME_TST) -DCOMPUTE_FLOP_NAME_TST=$(NAME_FLOP_TST) -DCOMPUTE_BYTES_NAME_TST=$(NAME_BYTES_TST) -c ../common/timer.c -o timer.o


$(OBJ_FILE_TST):$(FILE_TST)
	gcc $(CFLAGS) -DCOMPUTE_NAME=$(NAME_TST) -DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) -DCOMPUTE_BYTES_NAME=$(NAME_BYTES_TST) -c $(FILE_TST) -o $(OBJ_FILE_TST)

$(OBJ_FILE_DBG_TST):$(FILE_TST)
	gcc $(CFLAGS_DEBUG) -DCOMPUTE_NAME=$(NAME_TST) -DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) -DCOMPUTE_BYTES_NAME=$(NAME_BYTES_TST) -c $(FILE_TST) -o $(OBJ_FILE_DBG_TST)

build-timer: build-timer-infrastructure $(OBJ_FILE_TST)
	gcc -lm  $(OBJ_FILE_TST) timer.o -o ./run_timer.x

build-timer-debug: build-timer-infrastructure $(OBJ_FILE_DBG_TST)
	gcc -lm  $(OBJ_FILE_DBG_TST) timer.o -o ./run_timer_debug.x



####
# Do a smoke test for the same problem sizes as the benchmark
measure-verifier: build-verifier
	./run_verifier.x > $(RES_CSV_FILE_TST)
	../common/verify_output.sh $(RES_CSV_FILE_TST)


####
# Measure the performance in gflops
# Feel free to use parameters other than the defaults as
# they will give a more representative read of the performance
measure-performance: build-timer
	./run_timer.x |tee $(CSV_FILE_TST)


#####
# Cachegrind
# valgrind --tool=cachegrind --cache-sim=yes ./run_timer.x
#
# --cachegrind-out-file=<file>
#
#
#
# --I1=<size>,<associativity>,<line size>
# --D1=<size>,<associativity>,<line size>
# --LL=<size>,<associativity>,<line size> 
measure-cachegrind: build-timer-debug
#	valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=$(CACHEGRIND_FILE_TST) ./run_timer_debug.x 128 256 128 1 1   # Small size is fast.
	valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=$(CACHEGRIND_FILE_TST) ./run_timer_debug.x 1128 1256 128 1 1 # Large sizes accurate but super slow.
	cg_annotate $(CACHEGRIND_FILE_TST)




#####
# Objdump
# "How big is the code between the loops?"
# "How big is our instruction cache?"
measure-objdump: $(OBJ_FILE_DBG_TST)
	objdump -d $(OBJ_FILE_DBG_TST) > $(OBJDUMP_FILE_TST)
	objdump -S -d $(OBJ_FILE_DBG_TST) > $(OBJDUMP_ANNOTATED_FILE_TST)
	cat $(OBJDUMP_FILE_TST)
	cat $(OBJDUMP_ANNOTATED_FILE_TST)



######
# osaca
#
# osaca test_var000.s
# "What is the microarchitecture?"
# "Adjust --arch"
measure-osaca: venv $(FILE_TST)
	gcc $(CFLAGS) -DCOMPUTE_NAME=$(NAME_TST) -DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) -DUSE_OSACA=1 -S $(FILE_TST)  -o $(OSACA_ASM_FILE_TST)
	. venv/bin/activate;  osaca $(OSACA_FLAGS)  --ignore-unknown $(OSACA_ASM_FILE_TST)  > $(OSACA_FILE_TST)
	cat $(OSACA_FILE_TST)

#####
# llvm-mca
measure-llvm-mca: $(FILE_TST)
	gcc $(CFLAGS) -DCOMPUTE_NAME=$(NAME_TST) -DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) -DUSE_MCA=1 -S $(FILE_TST)  -o $(MCA_ASM_FILE_TST)
	llvm-mca $(MCA_ASM_FILE_TST)  > $(MCA_FILE_TST)
	cat $(MCA_FILE_TST)



measure-all: measure-llvm-mca measure-osaca measure-objdump measure-cachegrind plot

#####
# Asm
#
# "How do the assembly instructions relate to the code?"

dump-asm:
	gcc $(CFLAGS) -DCOMPUTE_NAME=$(NAME_TST) -DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST)  -S $(FILE_TST)



# Virtual environments activated and used in a makefile:
# https://stackoverflow.com/questions/24736146/how-to-use-virtualenv-in-makefile
venv: venv/touchfile
venv/touchfile: ../common/requirements.txt
	test -d venv || python3 -m venv venv
	. venv/bin/activate; pip install -Ur ../common/requirements.txt
	touch venv/touchfile


####
# plot results for a single run of the implementation
# with the default values. Note you can change the parameters
# and plot multiple lines on the same plot.
plot-variant: venv measure-performance
	. venv/bin/activate; ../common/plotter.py $(PNG_FILE_TST) $(CSV_FILE_TST) --peak=0.8 --min=0.7

plot-vs-baseline: venv measure-performance
	. venv/bin/activate; ../common/plotter.py "comparison-$(notdir $(FILE_TST)).png" $(FILE_REF).csv $(CSV_FILE_TST) --peak=0.8 --min=0.7

plot-all: plot-variant plot-vs-baseline

###
# Get the system details that are useful for these experiments
#
# Check the model number on CPU-WORLD
# https://www.cpu-world.com/cgi-bin/SearchSite.pl
#
# This will provide fine grain info on the hardware. Such
# as caches and associativity.
#
# We will use lscpu for this as it is a standard program
# likwid (likwid-topology) are also incredibly useful here
# as they provide a one-stop-shop for this info.
# https://github.com/RRZE-HPC/likwid/wiki/likwid-topology
get-system-info:
	lscpu
	@echo ""
	@echo "Search the model name on www.cpu-world.com"
	@echo ""
	@lscpu | grep -i "Model name:" | cut -d':' -f2- -

clean-all: clean clean-results

clean-results:
	rm -f $(MCA_FILE_TST) $(MCA_ASM_FILE_TST) $(OSACA_FILE_TST) $(OSACA_ASM_FILE_TST) $(OBJDUMP_ANNOTATED_FILE_TST) $(OBJDUMP_FILE_TST) $(OBJ_FILE_TST) $(OBJ_FILE_REF) $(CACHEGRIND_FILE_TST) $(CSV_FILE_TST) $(RES_CSV_FILE_TST) $(PNG_FILE_TST) $(OBJ_FILE_DBG_TST) $(OSACA_DOT_FILE_TST)

clean:
	rm -f *.o *.x *~ *.s
	rm -rf venv
