cmake_minimum_required(VERSION 3.15)
project(svm C)

set(CMAKE_C_STANDARD 99)

add_executable(svm src/main.c src/virtual_memory.h src/constants.h src/processor.h src/trap_routines.h)