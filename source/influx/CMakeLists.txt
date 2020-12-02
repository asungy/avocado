cmake_minimum_required( VERSION 3.19 )

add_library(
    Influx STATIC
    influx.cpp
    )

include_directories( third_party )
