cmake_minimum_required(VERSION 3.10)

project(d3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# Engine binary
add_executable(d3 "d3/engine/main.cpp")
target_include_directories(d3 PUBLIC
                            "${PROJECT_SOURCE_DIR}")

# Tests
find_library(GTEST_LIB gtest)

add_executable(unittests 
    "testing/unittests.cpp")
add_subdirectory(math)

target_include_directories(unittests PUBLIC
                            "${PROJECT_SOURCE_DIR}")

target_link_libraries(unittests PRIVATE 
    "${GTEST_LIB}")