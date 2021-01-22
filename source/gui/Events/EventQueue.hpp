#include "Event.hpp"

#include <queue>
#include <list>

namespace gui {
    class EventQueue
    {
    public:
        EventQueue();
        ~EventQueue();

        void PushEvent(Event * event);

        void ConsumeAll();

    private:
        void Consume();

    private:
        std::queue<Event *> * queue;
    };
}
