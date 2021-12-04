/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include"Renderer/Camera.h"
#include"Scene/SceneCamera.h"
#include"Scene/ScriptableEntity.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include<string>
namespace GU
{

    struct TransformComponent
    {
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
    };

    struct CameraComponent
    {
        SceneCamera Camera;
        bool Primary = true;
        CameraComponent() = default;
        CameraComponent(const CameraComponent& ) = default;
    };

    struct TagComponent
    {
        std::string Tag;
        TagComponent() = default;
        TagComponent(const TagComponent& ) = default;
        TagComponent(const std::string& tag)
            : Tag(tag){}
    };
    
    struct ColorComponet
    {
        glm::vec4 Color;
        ColorComponet()
            : Color({1.0f, 1.0f, 1.0f, 1.0f})
        {}
        ColorComponet(const ColorComponet&) = default;
        ColorComponet(const glm::vec4& color)
            : Color(color){}
        operator glm::vec4&() { return Color; }
    };

    struct V2PositionComponet
    {
        glm::vec2 Position;
        V2PositionComponet()
            : Position({0.0f, 0.0f})
        {}
        V2PositionComponet(const V2PositionComponet&) = default;
        V2PositionComponet(const glm::vec2& position)
            : Position(position){}
        operator glm::vec2&() { return Position; }
    };
    struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

    struct NativeScriptComponent
    {
        ScriptableEntity* Instance = nullptr;

        ScriptableEntity* (*InstantiateScript)();
        void (*DestroyScript)(NativeScriptComponent*);

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
        }

    };
}