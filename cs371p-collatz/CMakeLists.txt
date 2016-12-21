cmake_minimum_required(VERSION 3.3)
project(cs371p_collatz)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Collatz.c++
    Collatz.h
    RunCollatz.c++
    SphereCollatz.c++
    TestCollatz.c++
    vtn288-TestCollatz.c++)

add_executable(cs371p_collatz ${SOURCE_FILES})