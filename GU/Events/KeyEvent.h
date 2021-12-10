/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Events/Event.h"
namespace GU
{
    class KeyPressedEvent : public Event
    {
    public:
        KeyPressedEvent(uint32_t key)
            : m_keycode(key)
        {}
        ~KeyPressedEvent() = default;

        uint32_t GetKeyCode() const { return m_keycode; }

        GU_EVENT_GET_TYPE_OVERRIDE(KeyPressedEvent)

    private:
        uint32_t m_keycode;
    };
}
