/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include <memory>
#include "Core.h"
#include <string>
#include<functional>
#include"Events/Event.h"
namespace GU
{
    struct WindowProps
    {
        std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Gu Engine",
			        uint32_t width = 1600,
			        uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
    };

    
    class GU_API Window
    {
    private:

    public:
        using EventCallbackFn = std::function<void(Event&)>;
        struct WindowData
        {
            EventCallbackFn callback;
        };
        virtual void OnUpdate() = 0;
        virtual ~Window() = default;
        static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void* GetNativeWindow() = 0;
    };

}