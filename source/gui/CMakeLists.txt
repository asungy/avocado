cmake_minimum_required( VERSION 3.19 )

set( GLFW_BUILD_EXAMPLES "OFF" )
set( GLFW_BUILD_TESTS "OFF" )
set( GLFW_BUILD_DOCS "OFF" )

add_library(
    GUI STATIC
    Application.cpp
    Events/KeyboardEvent.cpp
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
