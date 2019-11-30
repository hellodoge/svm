cmake_minimum_required(VERSION 3.15)
project(svm C)

set(CMAKE_C_STANDARD 99)

add_executable(svm main.c virtual_memory.h constants.h instruction_handler.h processor.h interrupt.h)