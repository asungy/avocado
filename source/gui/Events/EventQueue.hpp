#include "Event.hpp"

#include <queue>

namespace gui {
    class EventQueue
    {
    public:
        EventQueue();
        ~EventQueue();

        void PushEvent(Event event);
        Event Consume();

    private:
        std::queue<Event> * event_queue;
    }
}
