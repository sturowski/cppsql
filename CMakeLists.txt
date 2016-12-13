cmake_minimum_required(VERSION 2.8.6)
project(cppsql)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


include_directories(/usr/include/mysql)
include_directories(src/query)
include_directories(src/connection)
include_directories(src/defines)
include_directories(src/table)
include_directories(src/tools)

set(SOURCE_FILES
        src/query/Query.h
        src/query/Query.cpp
        src/query/Select.h
        src/query/Select.cpp
        src/defines/Errors.h
        src/query/From.h
        src/query/From.cpp
        src/query/Join.cpp
        src/query/Join.h
        src/defines/Defines.h
        src/defines/Defines.cpp
        src/query/Where.cpp
        src/query/Where.h
        src/tools/ResourceManager.h
        src/connection/MysqlConnection.h
        src/connection/MysqlConnection.cpp
        src/connection/Connection.cpp
        src/connection/Connection.h
        src/table/Row.h
        src/table/Table.h
        src/table/Row.cpp
        src/table/Table.cpp
        src/query/Object.h
        src/query/Value.cpp
        src/query/Value.h src/parser/SelectParser.cpp src/parser/SelectParser.h)

add_executable(cppsql main.cpp ${SOURCE_FILES})
target_link_libraries(cppsql mysqlclient)
