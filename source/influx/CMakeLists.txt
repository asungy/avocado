cmake_minimum_required( VERSION 3.19 )

add_library(
    Influx STATIC
    influx.cpp
    )

include_directories( third_party )
include_directories( ../third_party/spdlog/include )

target_link_libraries(
    Influx PRIVATE
    spdlog::spdlog )
