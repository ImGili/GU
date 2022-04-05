#pragma once
#include <filesystem>
#include <memory>

#include <Renderer/Texture.h>
namespace GU
{
    class ContentBrowserPanel
    {
    private:
        std::filesystem::path m_CurrentDirectory;
        std::shared_ptr<Texture2D> m_FileIcon;
        std::shared_ptr<Texture2D> m_DirctoryIcon;
        /* data */
    public:
        ContentBrowserPanel();
        void OnImGuiRender();
    };
    
}