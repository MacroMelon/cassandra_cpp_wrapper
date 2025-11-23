cmake_minimum_required(VERSION 3.20)
project(cassandra_cpp_wrapper)

set(CMAKE_CXX_STANDARD 20)

#TODO - refactor into git submodule
#set(CASS_LIB_DIR /home/tharindu/projects/common_libs/cassandra-cpp-driver)


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/cassandra-cpp-driver/include)
#include_directories(${CASS_LIB_DIR}/include)

set(CASS_BUILD_STATIC ON)
set(CASS_BUILD_SHARED OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/cassandra-cpp-driver)

add_library(cassandra_cpp_wrapper STATIC src/cassandra_wrapper.cpp
        src/Session.cpp
        # include/Session.h ?
)

target_compile_options(cassandra_static PRIVATE -Wno-error=stringop-overread)

target_link_libraries(cassandra_cpp_wrapper cassandra_static)