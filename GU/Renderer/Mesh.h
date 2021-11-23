/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/VertexArray.h"
#include"Renderer/Buffer.h"
#include<glm/glm.hpp>
#include<vector>
#include<string>
namespace GU
{
    struct GU_API MeshVertex
    {
        MeshVertex(const glm::vec3& position)
            : Position(position)
        {}
        glm::vec3 Position;
    };
    
    class GU_API Mesh {
    public:
        Mesh(const std::vector<MeshVertex>& vdata,const std::vector<uint32_t>& idata);
        static std::shared_ptr<Mesh> Create(const std::vector<MeshVertex>& vdata,const std::vector<uint32_t>& idata);
        const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }
    private:
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::vector<MeshVertex> m_MeshVertexs;
        std::vector<uint32_t> m_MeshIndices;
    };
}