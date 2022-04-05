#version 330 core
layout (location = 0) in vec3 a_Posistion;
uniform mat4 u_ProjectionViewMatrix;
void main()
{
   gl_Position = u_ProjectionViewMatrix * vec4(a_Posistion, 1.0);
}