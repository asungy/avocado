cmake_minimum_required( VERSION 3.10 )

# Set project name
project( Avocado )

# Specify C++ compiler
set( CMAKE_CXX_COMPILER g++ )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

# Set header files
set( AVO_HEADER_FILES 
    source/python.hpp
    )

# Set source files
set( AVO_SOURCE_FILES
    source/main.cpp
    source/python.cpp
    )

# Add Python 3 API
find_package( Python 3.8 REQUIRED COMPONENTS Interpreter Development )
find_path( PYTHON_INCLUDE_PATH Python.h /usr/include/python3.8 )
include_directories( ${PYTHON_INCLUDE_PATH} )

# Add executable
add_executable( Avocado ${AVO_SOURCE_FILES} ${AVO_HEADER_FILES} )

# Specify libraries during linking
target_link_libraries( Avocado PRIVATE python3.8 )
