#include "Application.hpp"
#include "gui.hpp"

namespace gui {
    void Run() 
    {
        Application * app = Application::GetInstance();
        app->Run();
    }
}
