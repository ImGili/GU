#pragma once
#include"Core/Core.h"
namespace GU
{
    enum class EventType
    {
        None = 0,
        WindowsCloseEvent,
        MouseScrolledEvent,
        KeyPressedEvent
    };

    #define GU_EVENT_GET_TYPE_OVERRIDE(et) static EventType GetStaticType() { return EventType::et; }\
                                            EventType GetEventType() override { return GetStaticType();}
    class Event
    {
    public:
        bool Handled = false;
        virtual EventType GetEventType() = 0;
    };

    class EventProcess
    {
    public:
        EventProcess(Event& event)
            : m_Event(event)
        {}

        template<typename T, typename F>
        bool Process(F f)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled |= f(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };
}