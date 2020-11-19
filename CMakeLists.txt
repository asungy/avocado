cmake_minimum_required(VERSION 3.10)

# Set project name
project( Avocado )

# Set version
set ( PROJECT_VERSION_MAJOR 0 )
set ( PROJECT_VERSION_MINOR 1 )
set ( PROJECT_VERSION_PATCH 0 )

# Specify C++ standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

# Set header files
set( AVO_HEADER_FILES 
    source/interface.hpp
    )

# Set source files
set( AVO_SOURCE_FILES
    source/main.cpp
    source/interface.cpp
    )

# Set configuration variable directory
set( AVO_VARS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vars/" )
configure_file( ${AVO_VARS_DIR}/ProjectVars.hpp.in ProjectVars.hpp )

# Add Python 3
find_package( Python 3.8 REQUIRED COMPONENTS Interpreter Development )
find_path( PYTHON_INCLUDE_PATH Python.h /usr/include/python3.8 )
include_directories( ${PYTHON_INCLUDE_PATH} )

# Add executable
add_executable( Avocado ${AVO_SOURCE_FILES} ${AVO_HEADER_FILES} )

# Specify libraries during linking
target_link_libraries( Avocado PRIVATE python3.8 )

# Add include directory
target_include_directories( Avocado PRIVATE "${PROJECT_BINARY_DIR}" )
