#version 330 core
out vec4 FragColor;
in VS_OUT
{
   vec2 TexCoord;
} vs_in;
uniform sampler2D simple;
void main()
{
    FragColor = texture(simple, vs_in.TexCoord);
}