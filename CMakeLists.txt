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
project( Avocado CXX )

# Note: Specifying C++ compiler causes googletest to build in a loop
# set( CMAKE_CXX_COMPILER /usr/bin/g++ )

# Specify C++ compiler standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

# Set runtime output location
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# Set compiler flags
add_compile_options( -Wall -Werror -ggdb )

# Add internal libraries
add_subdirectory( source/python )
add_subdirectory( source/cmd )

# Create testing suite
if ( NOT DEFINED Build_Tests )
    set( Build_Tests OFF )
endif()
if ( Build_Tests )
    enable_testing()
    add_subdirectory( test )
endif()

# Add directories with header files
include_directories( source/python )
include_directories( source/cmd )

# Add executable
add_executable( Avocado source/main.cpp )

# Specify libraries during linking
target_link_libraries( Avocado PRIVATE PyInterface )
target_link_libraries( Avocado PRIVATE Command )

# Copy Python modules to build directory
file( COPY pymodules DESTINATION ${CMAKE_BINARY_DIR} )
