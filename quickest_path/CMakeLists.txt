# Minimum CMake version
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

# Include directories
include_directories(${INCLUDE_DIR})

# Define source files
set(SOURCES ${SRC_DIR}/utils.cpp)

# Main library
add_library(quickest_path_lib ${SOURCES})
target_include_directories(quickest_path_lib PUBLIC ${INCLUDE_DIR})

# Enable testing
enable_testing()

# Add tests
add_subdirectory(tests)