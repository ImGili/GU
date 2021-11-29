/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<glm/glm.hpp>
#include<string>
namespace GU
{
    struct GU_API TagComponent
    {
        std::string Tag;
        TagComponent() = default;
        TagComponent(const TagComponent& ) = default;
        TagComponent(const std::string& tag)
            : Tag(tag){}
    };
    
    struct GU_API ColorComponet
    {
        glm::vec4 Color;
        ColorComponet()
            : Color({1.0f, 1.0f, 1.0f, 1.0f})
        {}
        ColorComponet(const ColorComponet&) = default;
        ColorComponet(const glm::vec4& color)
            : Color(color){}
    };

    struct GU_API V2PositionComponet
    {
        glm::vec2 Position;
        V2PositionComponet()
            : Position({0.0f, 0.0f})
        {}
        V2PositionComponet(const V2PositionComponet&) = default;
        V2PositionComponet(const glm::vec2& position)
            : Position(position){}
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
}