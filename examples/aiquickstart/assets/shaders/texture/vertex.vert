#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (std140) uniform Camera
{
   mat4 ProjectionView;
}; 

out VS_OUT
{
   vec4 Color;
} vs_out;
void main()
{
   vs_out.Color = a_Color;
   gl_Position = ProjectionView * vec4(a_Position, 1.0);
}