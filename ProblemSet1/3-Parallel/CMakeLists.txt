cmake_minimum_required(VERSION 3.13)
project(3-Parallel)

set(CMAKE_CXX_STANDARD 14)

include_directories(/home/howiemalowie/Downloads/openmpi-4.0.0/ompi/include/)

add_executable(main Branching-Parallel.cpp)