cmake_minimum_required( VERSION 3.19 )

# Add Python 3 API
find_package( Python 3.8 REQUIRED COMPONENTS Interpreter Development )
find_path( PYTHON_INCLUDE_PATH Python.h /usr/include/python3.8 )
include_directories( ${PYTHON_INCLUDE_PATH} )

add_library(
    PyInterface STATIC
    python.cpp
    )

target_link_libraries( PyInterface PRIVATE python3.8 )
