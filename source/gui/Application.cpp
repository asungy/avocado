
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
        this->event_queue = new EventQueue();
        InitGlfwWindow();
    }

    Application::~Application()
    {
        delete this->event_queue;
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

            this->event_queue->ConsumeAll();
        }
    }

    void Application::InitGlfwWindow()
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
                std::cout << "Key: " << key << ", "
                          << "Scancode: " << scancode << ", "
                          << "Action: " << action << std::endl;
            };

            EventType event_type;
            switch (action) 
            {
            case GLFW_PRESS:
                event_type = EventType::KeyPressed;
                break;
            case GLFW_RELEASE:
                event_type = EventType::KeyReleased;
                break;
            default:
                event_type = EventType::None;
            }

            KeyboardEvent * event = new KeyboardEvent(event_type, EventCategoryKeyboard, args, f);

            Application::GetInstance()->event_queue->PushEvent(event);
        });
    }
}
