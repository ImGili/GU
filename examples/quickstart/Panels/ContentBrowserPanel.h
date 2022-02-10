#pragma once
#include <filesystem>
namespace GU
{
    class ContentBrowserPanel
    {
    private:
        std::filesystem::path m_CurrentDirectory;
        /* data */
    public:
        ContentBrowserPanel();
        void OnImGuiRender();
    };
    
}