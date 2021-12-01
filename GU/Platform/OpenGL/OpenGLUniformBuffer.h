/*
 * @Author: ImGili
 * @Description: 
 */
#include"Core/Core.h"
#include"Renderer/UniformBuffer.h"
namespace GU
{
    class OpenGLUniformBuffer : public UniformBuffer
    {
    public:
        OpenGLUniformBuffer(uint32_t size);
        void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;
        void Bind(uint32_t binding = 0) override;
        void Unbind() override;
        ~OpenGLUniformBuffer();
    private:
        uint32_t m_RendererID;
    };
}