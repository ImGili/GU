#pragma once
#include"Core/Core.h"
namespace GU
{
    enum class GU_API EventType
    {
        None = 0,
        WindowsCloseEvent
    };

    #define GU_EVENT_GET_TYPE_OVERRIDE(et) EventType GetEvent() override { return EventType::et;}
    class GU_API Event
    {
    public:
        virtual EventType GetEvent() = 0;
    };
}