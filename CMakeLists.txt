cmake_minimum_required(VERSION 3.10)

# Set the project name
set(PROJECT_NAME quickPathSE)
project(${PROJECT_NAME})

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(COMMON_INCLUDES 
    ${PROJECT_SOURCE_DIR}/includes/
)
include_directories(${COMMON_INCLUDES})

file(GLOB SRC_FILES 

    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/01-validate/*.cpp
    ${PROJECT_SOURCE_DIR}/src/02-extract/*.cpp
    ${PROJECT_SOURCE_DIR}/src/03-preprocess/*.cpp
    ${PROJECT_SOURCE_DIR}/src/04-load/*.cpp
    ${PROJECT_SOURCE_DIR}/src/05-pathFind/*.cpp
    ${PROJECT_SOURCE_DIR}/src/06-restApi/*.cpp

)


list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(quickPathSE_lib ${SRC_FILES})

# Add the executable
add_executable(quickPathSE
    src/main.cpp
)

target_link_libraries(quickPathSE quickPathSE_lib)

# Enable debugging symbols
#set(CMAKE_BUILD_TYPE Debug)

# TESTING

# Include directories



# Testing
# enable_testing()
# add_subdirectory(./googletest)
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

# # Ensure TEST_SRC_FILES is not empty
# if(TEST_SRC_FILES)
#     # Unit Tests
#     add_executable(runUnitTests ${TEST_SRC_FILES})

#     # Standard linking to gtest stuff
#     target_link_libraries(runUnitTests gtest gtest_main)

#     # Extra linking for the project
#     target_link_libraries(runUnitTests quickPathSE_lib)

#     # Add test
#     add_test(UnitTests runUnitTests)
# else()
#     message(WARNING "No test source files found.")
# endif()
