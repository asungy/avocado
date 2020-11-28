cmake_minimum_required( VERSION 3.19 )

# Set project name
project( Avocado )

# Specify C++ compiler
set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

# Set runtime output location
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# Enable testing for current directory and below
enable_testing()

# Set compiler flags
add_compile_options( -Wall -Werror -ggdb )

# Add internal libraries
add_subdirectory( source/python )
add_subdirectory( source/cmd )

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
