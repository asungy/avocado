# Do not allow in-source builds
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message(FATAL_ERROR
        "CMake generation for Avocado is not allowed within the source directory.\n"
        "Remove CMakeCache.txt and CMakeFiles/ and try again.\n"
        "mkdir build && cd build\n"
        "cmake .."
    )
endif()

cmake_minimum_required( VERSION 3.19 )

# Set project name
project( Avocado 
    HOMEPAGE_URL https://github.com/asungy/avocado
    LANGUAGES CXX 
)

# Note: Specifying C++ compiler causes googletest to build in a loop
# set( CMAKE_CXX_COMPILER /usr/bin/g++ )

# Specify C++ compiler standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

# Set runtime output location
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# Set compiler flags
# add_compile_options( -Wall -Werror -ggdb -O0 )
set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -Werror -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Werror -O3")

# Do not build tests for nlohmann_json library
set(JSON_BuildTests OFF CACHE INTERNAL "")

# Add internal libraries
add_subdirectory( source/influx )
add_subdirectory( source/python )
add_subdirectory( source/third_party/spdlog )
add_subdirectory( source/third_party/json )
add_subdirectory( source/cli )

# Add directories with header files
include_directories( source/cli )

# Create testing suite
if ( NOT DEFINED AVO_BuildTests )
    set( AVO_BuildTests OFF )
endif()
if ( Build_Tests )
    enable_testing()
    add_subdirectory( test )
endif()

# Add executable
add_executable( Avocado source/main.cpp )

# Specify libraries during linking
target_link_libraries( Avocado PRIVATE CLI )

# Copy Python modules to build directory
file( COPY pymodules DESTINATION ${CMAKE_BINARY_DIR} )
