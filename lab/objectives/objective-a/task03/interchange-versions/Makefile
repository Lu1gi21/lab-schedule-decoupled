# ssa-versions/Makefile

CFILES := $(wildcard ssa-*.c)
CSVFILES := $(CFILES:%=%.csv)

CFLAGS := -std=c99 -O2 -mavx2 -mfma -fopenmp -I../common
LDFLAGS := -lm

all: $(CSVFILES)

%.c.csv: %.c ../common/timer.c
	@echo "Generating CSV for $<"
	gcc $(CFLAGS) \
		-DCOMPUTE_NAME=compute_tst \
		-DCOMPUTE_FLOP_NAME=compute_flop_tst \
		-DCOMPUTE_BYTES_NAME=compute_bytes_tst \
		-c $< -o $<.o
	gcc $(CFLAGS) \
		-DCOMPUTE_NAME_TST=compute_tst \
		-DCOMPUTE_FLOP_NAME_TST=compute_flop_tst \
		-DCOMPUTE_BYTES_NAME_TST=compute_bytes_tst \
		-c ../common/timer.c -o timer.o
	gcc $<.o timer.o -o run_timer.x $(LDFLAGS)
	./run_timer.x | tee $@
	rm -f $<.o timer.o run_timer.x

clean:
	rm -f *.csv *.o *.x
