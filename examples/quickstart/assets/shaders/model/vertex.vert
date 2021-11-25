#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (std140) uniform Camera
{
   mat4 ProjectionView;
}; 
out VS_OUT
{
   vec2 TexCoord;
} vs_out;
void main()
{
   vs_out.TexCoord = a_TexCoord;
   gl_Position = ProjectionView * vec4(a_Position, 1.0);
}