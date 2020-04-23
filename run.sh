#!/bin/bash

declare -a modes=("updates" "populate")
declare -a progs=("aos" "soa" "aosoa")
declare -A times

for prog in "${progs[@]}"; do
   times[$prog]=0
done;

for mode in "${modes[@]}"; do
  for prog in "${progs[@]}"; do
     exectime=`bin/$prog.out $mode`
     echo "$prog $mode $exectime"
     times[${prog}]=$(bc -l <<< "${times[${prog}]} + ${exectime}")
  done;
done
for prog in "${progs[@]}"; do
   total=$(echo ${times[$prog]} | awk '{printf "%.3f", $0}')
   echo "$prog total $total"
done;
