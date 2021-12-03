/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include<glm/glm.hpp>
namespace GU
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const glm::mat4& projection)
            : Projection(projection)
        {}
        virtual ~Camera() = default;
        const glm::mat4& GetProjection() const { return Projection; }
    protected:
        glm::mat4 Projection = glm::mat4(1);
    };
}