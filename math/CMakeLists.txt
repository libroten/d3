cmake_minimum_required(VERSION 3.10)

project(d3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# All math unit tests sources
target_sources(unittests PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/matrix_unittest.cpp")