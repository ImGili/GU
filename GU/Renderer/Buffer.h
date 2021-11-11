/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Core/Assert.h"
#include<memory>
#include<string>
namespace GU
{
    enum class GU_API ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		GU_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
    struct GU_API BufferElement
    {
        // TODO: BufferElement Implement
        std::string Name;
        ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

        BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}
    };
    class GU_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetData(float* data, uint32_t size) = 0;

        static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);
    };
}
