cmake_minimum_required( VERSION 3.19 )

add_library(
    GUI STATIC
    gui.cpp
    )

add_subdirectory( third_party/glfw )
include_directories( third_party/glfw/include )

# Link OpenGL
find_package( OpenGL )
target_link_libraries( 
    GUI PRIVATE
    ${OPENGL_LIBRARIES}
    glfw
    )

# Link GLEW
find_package( GLEW REQUIRED )
target_link_libraries( GUI PRIVATE GLEW::GLEW )
