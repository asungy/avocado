#include "EventQueue.hpp"

namespace gui {
    EventQueue::EventQueue()
    {
        this->queue = new std::queue<Event *>();
    }

    EventQueue::~EventQueue()
    {
        delete this->queue;
    }

    void EventQueue::PushEvent(Event * event)
    {
        this->queue->push(event);
    }

    void EventQueue::Consume()
    {
        if ( this->queue->empty() )
            return;

        Event * event = this->queue->front();
        this->queue->pop();
        event->Process();
        delete event;
    }

    void EventQueue::ConsumeAll()
    {
        while( !this->queue->empty() )
        {
            this->Consume();
        }
    }
}
