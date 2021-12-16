/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Events/Event.h"
#include"Core/MouseCode.h"
namespace GU
{
    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset)
        {
        }

        float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

        GU_EVENT_GET_TYPE_OVERRIDE(MouseScrolledEvent)
    private:
        float m_XOffset, m_YOffset;
    };
    class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(const MouseKeyCode button)
			: m_Button(button) {}

		GU_EVENT_GET_TYPE_OVERRIDE(MouseButtonPressedEvent)
        const MouseKeyCode GetMouseButton() const { return m_Button; }
    private:
        MouseKeyCode m_Button;
	};
}
