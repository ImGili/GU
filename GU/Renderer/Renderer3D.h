/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Model.h"
#include"Renderer/Mesh.h"
#include"Renderer/EditorCamera.h"
namespace GU
{
    class GU_API Renderer3D
    {
    public:
        static void Init();
        static void BeginScene(EditorCamera camera);
        static void DrawMesh(const std::shared_ptr<Mesh>& Mesh);
        static void EndScene();

    private:
        static void Flush();
    };
}