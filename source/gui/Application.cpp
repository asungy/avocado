
#include "Application.hpp"

#include "Events/KeyboardEvent.hpp"

#include <iostream>

namespace gui {
    Application * Application::instance = nullptr;

    Application * Application::GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new Application();
        }
        return instance;
    }

    Application::Application()
    {
        if (!glfwInit())
            return;

        this->window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!this->window)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(this->window);

        glfwSetKeyCallback(this->window, [](GLFWwindow * window, int key, int scancode, int action, int mods){
            // if (key == GLFW_KEY_E && action == GLFW_PRESS) std::cout << "E key pressed" << std::endl;
            KeyboardEventArgs args = { window, key, scancode, action, mods };

            auto f = [](GLFWwindow * window, int key, int scancode, int action, int mods){
                std::cout << "From the callback!" << std::endl;
            };

            KeyboardEvent event{EventType::None, EventCategoryKeyboard, args, f };

            event.Process();
        });
    }

    Application::~Application()
    {
        glfwTerminate();
    }

    void Application::Run()
    {
        std::cout << "Hello GUI!" << std::endl;

        while (!glfwWindowShouldClose(this->window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(this->window);

            glfwPollEvents();
        }
    }
}
