cmake_minimum_required(VERSION 3.10)
project(QuickestPathProject)

# Add Google Test
add_subdirectory(googletest)

# Include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Source files
set(SOURCE_FILES src/extraction/csv_reader.cpp src/extraction/binary_writer.cpp src/extraction/extract.cpp)

# Test files
set(TEST_FILES src/extraction/tests/test_csv_reader.cpp src/extraction/tests/test_binary_writer.cpp)

# Add the main executable
add_executable(extract ${SOURCE_FILES})

# Add the test executable
add_executable(run_tests ${TEST_FILES})

# Link Google Test libraries
target_link_libraries(run_tests gtest gtest_main)