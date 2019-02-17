#!/bin/bash

module load mpi/openmpi-x86_64

mpiCC -g -std=c++11 -W -Wall -Winline -Wextra -o output Cellular2D-Parallel.cpp

rm results2D2.txt

N=( 8192 16384 32768 65536 )
processes=( 64 128 256 512 )

printf "%15s" "${processes[@]}"  >> results2D2.txt
for i in "${N[@]}"
do
  	result=()
        for p in "${processes[@]}"
        do
		echo Running "$i" with "$p" processes
          	result=("${result[@]}" $(mpiexec -n "$p" output Gameoflife.txt gameoflife"$i".txt 1))
        done
	printf "\n $i" >> results2D2.txt
        printf "%15s" "${result[@]}" >> results2D2.txt
done

