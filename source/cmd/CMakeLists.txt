add_library(
    Command STATIC
    command.cpp
    )

include_directories( third_party )

# Adding PyInterface library 
target_link_libraries( Command PRIVATE PyInterface )
