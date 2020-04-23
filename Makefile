
.PHONY: all build run clean

SRC=aos soa aosoa
PROGS=$(addprefix bin/,$(SRC:=.out))

all: run

bin/%.out: src/%.c src/common.h
	@mkdir -p bin
	gcc -std=c11 -march=native -Wall -O3 -o $@ $<
	
# -fopt-info-vec-all 2> $($@:.out=.infos)

build: $(PROGS)

run: build
	@./run.sh

clean: 
	rm -Rf bin

