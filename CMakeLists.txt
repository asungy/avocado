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

# Set configuration variable directory
set( AVO_VARS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vars/" )
configure_file( ${AVO_VARS_DIR}/ProjectVars.hpp.in ProjectVars.hpp )

# Set source directory
# TODO: Refactor: GLOB-ing source files is not recommended because this makes CMAKE
#       unaware of file changes and the generators won't function properly
set( AVO_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/" )
file( GLOB AVO_SOURCE_FILES "${AVO_SOURCE_DIR}/*.cpp" )

# Add Python 3
find_package( Python 3.8 REQUIRED COMPONENTS Interpreter Development )
find_path( PYTHON_INCLUDE_PATH Python.h /usr/include/python3.8 )
include_directories( ${PYTHON_INCLUDE_PATH} )

# Add executable
add_executable( Avocado ${AVO_SOURCE_FILES} )

# Specify libraries during linking
target_link_libraries( Avocado python3.8 )

# Add include directory
target_include_directories( Avocado PUBLIC "${PROJECT_BINARY_DIR}" )
