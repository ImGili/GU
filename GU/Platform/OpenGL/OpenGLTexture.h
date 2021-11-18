/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Texture.h"
#include<glad/glad.h>
namespace GU
{
    class GU_API OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);

        void Bind(uint32_t slot) override;

        void SetData(void* data, uint32_t size) override;
    private:
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
        uint32_t m_Width, m_Height;
    };
}