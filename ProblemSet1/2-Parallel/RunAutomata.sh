#!/bin/bash

#module load mpi/openmpi-x86_64
mpiCC -std=c++11 ../1-Parallel/Cellular1D-Parallel.cpp -O3 -o 1parallel.o
mpiCC -std=c++11 ../2-Parallel/Cellular2D-Parallel.cpp -O3 -o 2parallel.o

rm output/results2D.txt

N=( 1024 2048 4096 8192 16384 32768 65536 )
processes=( 32 64 128 256 512 ) 

printf "%15s" "${processes[@]}"  >> output/results2D.txt
for i in "${N[@]}"
do
	result=()
	for p in "${processes[@]}"
	do
		result=("${result[@]}" $(mpiexec -n "$p" ./2parallel.o rules/gameoflife.txt input/gameoflife"$i".txt 1))
	done
	printf "\n $i" >> output/results2D.txt
	printf "%15s" "${result[@]}" >> output/results2D.txt
done
