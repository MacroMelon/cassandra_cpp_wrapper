cmake_minimum_required(VERSION 3.20)
project(cassandra_cpp_wrapper)

set(CMAKE_CXX_STANDARD 20)

#TODO - refactor into git submodule
#set(CASS_LIB_DIR /home/tharindu/projects/common_libs/cassandra-cpp-driver)


include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${CASS_LIB_DIR}/include)

add_subdirectory(/home/tharindu/projects/common_libs/cassandra-cpp-driver)

add_library(cassandra_cpp_wrapper STATIC src/cassandra_wrapper.cpp
        src/Session.cpp
        # include/Session.h ?
)
