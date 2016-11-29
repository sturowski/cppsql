# CMake build script for cppsql

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(cppsql)
include_directories(src)

set(SOURCE_FILES
        src/querybuilder.h
        src/querybuilder.cpp
        src/select.h
        src/select.cpp
        src/errors.h
        src/from.h
        src/from.cpp
        src/join.cpp
        src/join.h
        src/defines.h
        src/defines.cpp
        src/where.cpp
        src/where.h)


# The main.cpp is only for testen and developing the classes
add_executable(cppsql main.cpp ${SOURCE_FILES})
