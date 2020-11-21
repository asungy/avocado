cmake_minimum_required( VERSION 3.10 )

# Set project name
project( Avocado )

# Specify C++ compiler
set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

# Add internal libraries
add_subdirectory( source/python )

# Add directories with header files
include_directories( source/python )

# Add executable
add_executable( Avocado source/main.cpp )

# Specify libraries during linking
target_link_libraries( Avocado PRIVATE py-interface )

# Copy Python modules to build directory
file( COPY pymodules DESTINATION ${CMAKE_BINARY_DIR} )
