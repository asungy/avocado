cmake_minimum_required( VERSION 3.19 )

add_subdirectory( googletest )

include_directories( ../source/influx )

add_executable( AvocadoTest influx_test.cpp )

target_link_libraries( AvocadoTest PRIVATE gtest_main Influx )

add_test( 
    NAME AvocadoTest
    COMMAND AvocadoTest
)
