cmake_minimum_required( VERSION 2.8 )
project(huffman)
 
set( CMAKE_BUILD_TYPE Release )
 
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )
 
add_executable(huffman sort.c huffman.c main.c)
