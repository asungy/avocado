#include "Application.hpp"
#include "gui.hpp"

namespace gui {
    void Run() 
    {
        Application * app = new Application();
        app->Run();
    }
}
