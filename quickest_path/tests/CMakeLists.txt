# Collect test source files
set(TEST_SOURCES ${TEST_DIR}/test_utils.cpp)

# Add the test executable
add_executable(test_suite ${TEST_SOURCES})

# Include directories for the tests
include_directories(${INCLUDE_DIR})

target_link_libraries(test_suite GTest::gtest GTest::gtest_main quickest_path_lib pthread)

add_test(NAME test_suite COMMAND test_suite)