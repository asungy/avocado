#pragma once

#include <string>

namespace gui {
    enum class EventType
    {
        None = 0,
        KeyPressed,
        KeyReleased
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryKeyboard = 1 << 0
    };

    class Event
    {
    public:
        Event(EventType event_type, int category_flag) 
            : event_type(event_type), category_flag(category_flag) {};

        virtual ~Event() = default;
        
        // Returns the string representation of this event. Used for logging
        // and debugging purposes.
        virtual std::string ToString() const = 0;

        // Process the event by executing the associated callback
        virtual void Process() = 0;

        // Returns the enum class EventType of this event. Used for targeting
        // specific event types.
        EventType GetEventType() const { return this->event_type; }

        // Check if the event has been processed
        bool IsHandled() const { return this->handled; };

        // Returns the category flag for this event
        int GetCategoryFlag() const { return category_flag; }

    private:
        EventType event_type = EventType::None;
        bool handled = false;
        int category_flag = 0;
    };
}
