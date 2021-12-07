#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout (std140) uniform Camera
{
   mat4 ProjectionView;
}; 

out VS_OUT
{
   vec4 Color;
	vec2 TexCoord;
   float v_TexIndex;
} vs_out;
void main()
{
   vs_out.Color = a_Color;
   vs_out.TexCoord = a_TexCoord;
   vs_out.v_TexIndex = a_TexIndex;
   gl_Position = ProjectionView * vec4(a_Position, 1.0);
}