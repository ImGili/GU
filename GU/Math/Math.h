/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include<glm/glm.hpp>
namespace GU
{
    namespace Math
    {
        bool Decompose(const glm::mat4& modelMatrix, glm::vec3& scale, glm::vec3& rotation, glm::vec3& translation);
    }
}