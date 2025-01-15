# Find GoogleTest package
find_package(GTest REQUIRED)

# Collect test source files
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_utils.cpp)

# Add test executable
add_executable(test_suite ${TEST_SOURCES})

# Link libraries to the test executable
target_link_libraries(test_suite GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main pthread)

# Add tests to CTest
add_test(NAME RunTests COMMAND test_suite)