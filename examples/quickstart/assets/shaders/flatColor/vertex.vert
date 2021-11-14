#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 u_ProjectionViewMatrix;
void main()
{
   gl_Position = u_ProjectionViewMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}