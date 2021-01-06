#include "GLFW/glfw3.h"

#include "Application.hpp"

#include <iostream>

void Application::Run()
{
    std::cout << "Hello GUI!" << std::endl;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, [](GLFWwindow * window, int key, int scancode, int action, int mods){
        if (key == GLFW_KEY_E && action == GLFW_PRESS) std::cout << "E key pressed" << std::endl;
    });

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
