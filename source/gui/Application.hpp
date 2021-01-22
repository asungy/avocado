#pragma once

#include "GLFW/glfw3.h"

#include "Events/EventQueue.hpp"

namespace gui {
    class Application 
    {
    public:
        static Application * GetInstance();
        void Run();

    private:
        Application();
        ~Application();

        void InitGlfwWindow();

    private:
        static Application * instance;
        GLFWwindow * window;
        EventQueue * event_queue;
    };
}
