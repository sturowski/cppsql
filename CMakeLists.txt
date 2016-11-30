cmake_minimum_required(VERSION 2.8.6)
project(cppsql)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(/usr/include/mysql)
include_directories(src/query)
include_directories(src/connection)
include_directories(src/defines)
include_directories(src/table)
include_directories(src/tools)

set(SOURCE_FILES
        src/query/query.h
        src/query/query.cpp
        src/query/select.h
        src/query/select.cpp
        src/defines/errors.h
        src/query/from.h
        src/query/from.cpp
        src/query/join.cpp
        src/query/join.h
        src/defines/defines.h
        src/defines/defines.cpp
        src/query/where.cpp
        src/query/where.h
        src/tools/resourcemanager.h
        src/connection/mysqlconnection.h
        src/connection/mysqlconnection.cpp
        src/connection/connection.cpp
        src/connection/connection.h
        src/table/row.h
        src/table/table.h
        src/table/row.cpp
        src/table/table.cpp
        src/query/object.h
        src/query/value.cpp
        src/query/value.h)

add_executable(cppsql main.cpp ${SOURCE_FILES})
target_link_libraries(cppsql mysqlclient)
