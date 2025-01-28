file(GLOB SRC_FILES 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Remove main.cpp from the list
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Check if there are source files for the library
if(SRC_FILES)
    add_library(quickPathSE_lib ${SRC_FILES})
else()
    message(WARNING "No source files found for quickPathSE_lib. Skipping library creation.")
endif()

# Add the executable
add_executable(quickPathSE
    src/main.cpp
)

# Link the library if it exists
if(TARGET quickPathSE_lib)
    target_link_libraries(quickPathSE quickPathSE_lib)
endif()