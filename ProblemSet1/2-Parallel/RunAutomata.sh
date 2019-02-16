#!/bin/bash

module load mpi/openmpi-x86_64

mpiCC -g -std=c++11 -W -Wall -Winline -Wextra -o output Cellular2D-Parallel.cpp

rm output/results2D.txt

N=( 1024 2048 4096 8192 16384 32768 65536 )
processes=( 32 64 128 256 512 ) 

printf "%15s" "${processes[@]}"  >> output/results2D.txt
for i in "${N[@]}"
do
	result=()
	for p in "${processes[@]}"
	do
		result=("${result[@]}" $(mpiexec -n "$p" output gameoflife.txt gameoflife"$i".txt 1))
	done
	printf "\n $i" >> output/results2D.txt
	printf "%15s" "${result[@]}" >> output/results2D.txt
donels
