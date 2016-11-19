cmake_minimum_required(VERSION 3.5.0)
project(cppsql)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(/usr/include/mysql)
include_directories(src/query)
include_directories(src/connection)

set(SOURCE_FILES
        src/query/query.h
        src/query/query.cpp
        src/query/select.h
        src/query/select.cpp
        src/query/errors.h
        src/query/from.h
        src/query/from.cpp
        src/query/join.cpp
        src/query/join.h
        src/query/defines.h
        src/query/defines.cpp
        src/query/where.cpp
        src/query/where.h
        src/query/resourcemanager.h
        src/connection/mysqlconnection.h
        src/connection/mysqlconnection.cpp
        src/connection/connection.cpp
        src/connection/connection.h
        src/connection/row.h src/connection/table.h src/connection/row.cpp src/connection/table.cpp)

add_executable(cppsql main.cpp ${SOURCE_FILES})
target_link_libraries(cppsql mysqlclient)
