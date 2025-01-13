# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(quickest_path LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Add the include directory for headers
include_directories(${INCLUDE_DIR})

# Add source files
set(SOURCES ${SRC_DIR}/utils.cpp)

# Add the main library (this will be shared with the tests)
add_library(quickest_path_lib ${SOURCES})


# Enable testing
enable_testing()

