cmake_minimum_required( VERSION 3.19 )

add_library(
    REPL STATIC
    repl.cpp
    )

target_link_libraries( REPL PRIVATE ncursesw )
