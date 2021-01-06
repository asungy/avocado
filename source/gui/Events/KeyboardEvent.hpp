#pragma once

#include "GLFW/glfw3.h"

#include "Event.hpp"

#include <functional>

using KeyboardEventCallback = std::function<void(GLFWwindow *, int, int, int, int)>;

namespace gui {
   struct KeyboardEventArgs
   {
       GLFWwindow * window;
       int key;
       int scancode;
       int action;
       int mods;
   };

    class KeyboardEvent : public Event
    {
    public:
       KeyboardEvent( 
           EventType event_type, 
           int category_flag, 
           KeyboardEventArgs args, 
           KeyboardEventCallback callback
       );

       std::string ToString() const override { return "hello"; };

       void Process() override { 
           callback(this->args.window, this->args.key, this->args.scancode, this->args.action, 
                    this->args.mods);
       };

    private:
        KeyboardEventCallback callback;
        KeyboardEventArgs args;
    };
}
