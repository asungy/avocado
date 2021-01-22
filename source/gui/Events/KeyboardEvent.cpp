#include "KeyboardEvent.hpp"

namespace gui {
   KeyboardEvent::KeyboardEvent(
       EventType event_type, 
       int category_flag, 
       KeyboardEventArgs args, 
       KeyboardEventCallback callback
   ) 
       : Event(event_type, category_flag)
   {
        this->callback = callback;
        this->args = args;
   };
}
