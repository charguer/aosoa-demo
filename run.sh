#!/bin/bash

declare -a modes=("updates" "populate")
declare -a progs=("aos" "soa" "aosoa")

for prog in "${progs[@]}"; do
   gcc -std=c11 -march=native -Wall -O3 -o bin/$prog src/$prog.c -fopt-info-vec-all 2> bin/aos_infos.txt
done

for mode in "${modes[@]}"; do
  for prog in "${progs[@]}"; do
     echo "$prog $mode"
     bin/$prog $mode
  done;
done
