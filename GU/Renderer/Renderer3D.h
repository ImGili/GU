/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Model.h"
#include"Renderer/Mesh.h"
namespace GU
{
    class GU_API Renderer3D
    {
    public:
        static void Init();
        static void BeginScene();
        static void DrawMesh(const std::shared_ptr<Mesh>& Mesh);
        static void EndScene();

    private:
        static void Flush();
    };
}