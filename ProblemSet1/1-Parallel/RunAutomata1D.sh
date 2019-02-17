#!/bin/bash
 
module load mpi/openmpi-x86_64
mpiCC -g -std=c++11 -W -Wall -Winline -Wextra -o output Cellular1D-Parallel.cpp

 
rm results1D.txt
echo Running parallel 1D automata

k=(10 11 12 13 14 15 16 17 18 19 20) 
processes=( 2 4 8 16 32 64 128 256 512 )
 
printf "%15s" "${processes[@]}"  >> results1D.txt
for i in "${k[@]}"
do
	result=()
	for p in "${processes[@]}"
	do
    		echo running "$i" on "$p" processes
    		result=("${result[@]}" $(mpiexec -n "$p" output mod2.txt 1 "$i"))
	done
	printf "\n $i" >> results1D.txt
	printf "%15s" "${result[@]}" >> results1D.txt
done
