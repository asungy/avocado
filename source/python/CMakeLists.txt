
# Add Python 3 API
find_package( Python 3.8 REQUIRED COMPONENTS Interpreter Development )
find_path( PYTHON_INCLUDE_PATH Python.h /usr/include/python3.8 )
include_directories( ${PYTHON_INCLUDE_PATH} )

add_library(
    py-interface
    python.cpp
    )

target_link_libraries( py-interface PRIVATE python3.8 )
