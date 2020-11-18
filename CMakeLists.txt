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

set( AVO_VARS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vars/" )

configure_file( ${AVO_VARS_DIR}/ProjectVars.hpp.in ProjectVars.hpp )

add_executable( Avocado main.cpp )

target_include_directories( Avocado PUBLIC "${PROJECT_BINARY_DIR}" )
