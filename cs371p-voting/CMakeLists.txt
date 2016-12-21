cmake_minimum_required(VERSION 3.3)
project(cs371p-voting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Voting.c++ UVaVoting.c++ UVaVoting.h)
add_executable(cs371p-voting ${SOURCE_FILES})