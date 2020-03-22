cmake_minimum_required(VERSION 3.15)
project(svm C)

set(CMAKE_C_STANDARD 99)

add_executable(svm src/main.c
        src/processor.c
        src/trap_routines.c
        src/vm_memory.c
        src/vm_malloc.c
        src/vm_memory.h
        src/constants.h
        src/processor.h
        src/trap_routines.h
        src/vm_malloc.h)