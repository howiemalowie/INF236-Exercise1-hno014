cmake_minimum_required(VERSION 3.13)
project(Cellular1D-Parallel)

set(CMAKE_CXX_STANDARD 14)

include_directories(/home/howiemalowie/Downloads/openmpi-4.0.0/ompi/include/)

add_executable(Cellular1D-Parallel Cellular1D-Parallel.cpp)