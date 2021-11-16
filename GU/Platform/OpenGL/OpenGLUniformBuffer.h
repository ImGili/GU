/*
 * @Author: ImGili
 * @Description: 
 */
#include"Core/Core.h"
#include"Renderer/UniformBuffer.h"
namespace GU
{
    class GU_API OpenGLUniformBuffer : public UniformBuffer
    {
    public:
        OpenGLUniformBuffer(uint32_t size, uint32_t binding = 0);
        void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;
        void Bind() override;
        void Unbind() override;
        ~OpenGLUniformBuffer();
    private:
        uint32_t m_RendererID;
    };
}