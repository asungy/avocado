cmake_minimum_required( VERSION 3.19 )

add_subdirectory( googletest )

include_directories( ../source/cmd )

add_executable( AvocadoTest command_test.cpp )

target_link_libraries( AvocadoTest PRIVATE gtest_main Command )

add_test( 
    NAME AvocadoTest
    COMMAND AvocadoTest
)
