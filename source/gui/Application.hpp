#pragma once

#include "GLFW/glfw3.h"

namespace gui {
    class Application 
    {
    public:
        static Application * GetInstance();
        void Run();

    private:
        Application();
        ~Application();

    private:
        static Application * instance;
        GLFWwindow * window;

    };
}
