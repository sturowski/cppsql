cmake_minimum_required(VERSION 2.8.6)
project(cppsql)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
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
        src/where.h
        src/resourcemanager.h
)
add_executable(cppsql ${SOURCE_FILES})
