# === Configurable Inputs ===
FILE_TST ?= example.c
TASK_DIR ?= task11
TST_PATH := $(TASK_DIR)/$(FILE_TST)

FILE_REF := ../objective-a/task00/ssa-versions/ssa_blur_2x2_baseline.c
COMMON_DIR := common

OBJ_FILE_TST := $(TST_PATH).o
OBJ_FILE_DBG_TST := $(TST_PATH).dbg.o
OBJ_FILE_REF := $(FILE_REF).ref.o

CSV_FILE_TST := $(TST_PATH).csv
RES_CSV_FILE_TST := $(TST_PATH).res.csv
PNG_FILE_TST := $(TST_PATH).png

NAME_TST := compute_tst
NAME_REF := compute_ref
NAME_FLOP_TST := compute_flop_tst
NAME_FLOP_REF := compute_flop_ref
NAME_BYTES_TST := compute_bytes_tst
NAME_BYTES_REF := compute_bytes_ref

CFLAGS ?= -std=c99 -O2 -mavx2 -mfma -fopenmp -I$(COMMON_DIR)
CFLAGS_DEBUG := $(CFLAGS) -g

# === Default target ===
all: measure-performance

# === Build rules ===

build-verifier:
	gcc $(CFLAGS_DEBUG) -c verifier.c -o verifier.o
	gcc $(CFLAGS_DEBUG) \
		-DCOMPUTE_NAME=$(NAME_REF) \
		-DCOMPUTE_FLOP_NAME=$(NAME_FLOP_REF) \
		-DCOMPUTE_BYTES_NAME=$(NAME_BYTES_REF) \
		-c $(FILE_REF) -o $(OBJ_FILE_REF)
	gcc $(CFLAGS_DEBUG) \
		-DCOMPUTE_NAME=$(NAME_TST) \
		-DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) \
		-DCOMPUTE_BYTES_NAME=$(NAME_BYTES_TST) \
		-c $(TST_PATH) -o $(OBJ_FILE_TST)
	gcc -lm $(OBJ_FILE_REF) $(OBJ_FILE_TST) verifier.o -o $(TASK_DIR)/run_verifier.x

build-timer:
	gcc $(CFLAGS) \
		-DCOMPUTE_NAME=$(NAME_TST) \
		-DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) \
		-DCOMPUTE_BYTES_NAME=$(NAME_BYTES_TST) \
		$(TST_PATH) $(COMMON_DIR)/timer.c -lm -o $(TASK_DIR)/run_timer.x

build-timer-debug:
	gcc $(CFLAGS_DEBUG) \
		-DCOMPUTE_NAME=$(NAME_TST) \
		-DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) \
		-DCOMPUTE_BYTES_NAME=$(NAME_BYTES_TST) \
		-c $(TST_PATH) -o $(OBJ_FILE_DBG_TST)
	gcc $(CFLAGS_DEBUG) \
		-DCOMPUTE_NAME=$(NAME_TST) \
		-DCOMPUTE_FLOP_NAME=$(NAME_FLOP_TST) \
		-DCOMPUTE_BYTES_NAME=$(NAME_BYTES_TST) \
		$(OBJ_FILE_DBG_TST) $(COMMON_DIR)/timer.c -lm -o $(TASK_DIR)/run_timer_debug.x

# === Measurement and plotting ===

measure-performance: build-timer
	./$(TASK_DIR)/run_timer.x | tee $(CSV_FILE_TST)

measure-verifier: build-verifier
	./$(TASK_DIR)/run_verifier.x > $(RES_CSV_FILE_TST)
	./verify_output.sh $(RES_CSV_FILE_TST)

plot-variant: venv measure-performance
	. venv/bin/activate; $(COMMON_DIR)/plotter.py $(PNG_FILE_TST) $(CSV_FILE_TST) --peak=3 --min=0

plot-vs-baseline: venv measure-performance
	. venv/bin/activate; $(COMMON_DIR)/plotter.py "$(TASK_DIR)/comparison-$(notdir $(FILE_TST)).png" $(FILE_REF).csv $(CSV_FILE_TST) --peak=3 --min=0

plot-all: plot-variant plot-vs-baseline

# === Python env ===

venv: venv/touchfile
venv/touchfile: $(COMMON_DIR)/requirements.txt
	test -d venv || python3 -m venv venv
	. venv/bin/activate; pip install -Ur $(COMMON_DIR)/requirements.txt
	touch venv/touchfile

# === Cleanup ===
clean-results:
	rm -f $(OBJ_FILE_TST) $(OBJ_FILE_DBG_TST) $(OBJ_FILE_REF) \
		$(CSV_FILE_TST) $(RES_CSV_FILE_TST) $(PNG_FILE_TST) \
		$(TASK_DIR)/run_timer.x $(TASK_DIR)/run_timer_debug.x \
		$(TASK_DIR)/comparison-$(notdir $(FILE_TST)).png

clean:
	rm -f *.o *~ *.x *.s
	rm -rf venv
