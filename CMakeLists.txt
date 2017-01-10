cmake_minimum_required(VERSION 2.8.6)
project(cppsql)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


include_directories(/usr/include/mysql)
include_directories(src/query)
include_directories(src/query/workflow)
include_directories(src/connection)
include_directories(src/defines)
include_directories(src/table)
include_directories(src/tools)
include_directories(src/parser)

set(HEADER_FILES
        src/query/Query.h
        src/query/Select.h
        src/defines/Errors.h
        src/query/From.h
        src/query/Join.h
        src/defines/Defines.h
        src/query/Where.h
        src/tools/ResourceManager.h
        src/connection/MysqlConnection.h
        src/connection/Connection.h
        src/table/Row.h
        src/table/Table.h
        src/query/Object.h
        src/query/Value.h
        src/parser/SelectParser.h
        src/parser/ParseHelper.h
        src/parser/FromParser.h
        src/query/Params.h
        src/query/Set.h
)

set(SOURCE_FILES
        src/query/Query.cpp
        src/query/Select.cpp
        src/query/From.cpp
        src/query/Join.cpp
        src/defines/Defines.cpp
        src/query/Where.cpp
        src/connection/MysqlConnection.cpp
        src/connection/Connection.cpp
        src/table/Row.cpp
        src/table/Table.cpp
        src/query/Value.cpp
        src/parser/SelectParser.cpp
        src/parser/FromParser.cpp
        src/query/Params.cpp
        src/query/Set.cpp)

add_executable(cppsql_test main.cpp ${SOURCE_FILES})
target_link_libraries(cppsql_test mysqlclient)

add_library(cppsql ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(cppsql mysqlclient)

# Copy all Headers in one folder
FOREACH(FILE ${HEADER_FILES})
get_filename_component(barename ${FILE} NAME)
add_custom_command(
        TARGET cppsql POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/${FILE}
        ${CMAKE_CURRENT_BINARY_DIR}/include/${barename})
ENDFOREACH()
