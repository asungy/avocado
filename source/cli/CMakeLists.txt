cmake_minimum_required( VERSION 3.19 )

add_library(
    CLI STATIC
    cli.cpp
    )

include_directories( third_party )

# Adding PyInterface library 
target_link_libraries( 
    CLI PRIVATE 
    Influx
    PyInterface )
