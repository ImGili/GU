#version 330 core
out vec4 FragColor;

in VS_OUT
{
   vec4 Color;
} vs_in;
void main()
{
    
    FragColor = vs_in.Color;
}