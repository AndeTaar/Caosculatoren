cmake_minimum_required(VERSION 3.27)
project(Caosculatoren C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SOURCE_FILES caosculator.cpp)
add_executable(Caosculatoren caosculator.c
        caosculator.h
        test_caosculator.c
        bitoperations.c
        bitoperations.h)
