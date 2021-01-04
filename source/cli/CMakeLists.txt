cmake_minimum_required( VERSION 3.19 )

add_library(
    CLI STATIC
    cli.cpp
    )

include_directories( third_party )
include_directories( ../third_party/spdlog/include )
include_directories( ../third_party/json/include )

# Adding PyInterface library 
target_link_libraries( 
    CLI PRIVATE 
    Influx
    PyInterface 
    GUI
    spdlog::spdlog 
    nlohmann_json::nlohmann_json
    )
