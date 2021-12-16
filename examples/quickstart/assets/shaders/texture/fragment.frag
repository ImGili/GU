#version 330 core
layout(location = 0)out vec4 FragColor1;
layout(location = 1)out vec4 FragColor2;

in VS_OUT
{
    vec4 Color;
    vec2 TexCoord;
    float v_TexIndex ;
} vs_in;
uniform sampler2D u_Textures[16];
void main()
{
    vec4 texColor = vs_in.Color;
	switch(int(vs_in.v_TexIndex))
	{
		case  0: texColor *= texture(u_Textures[ 0], vs_in.TexCoord); break;
		case  1: texColor *= texture(u_Textures[ 1], vs_in.TexCoord); break;
		case  2: texColor *= texture(u_Textures[ 2], vs_in.TexCoord); break;
		case  3: texColor *= texture(u_Textures[ 3], vs_in.TexCoord); break;
		case  4: texColor *= texture(u_Textures[ 4], vs_in.TexCoord); break;
		case  5: texColor *= texture(u_Textures[ 5], vs_in.TexCoord); break;
		case  6: texColor *= texture(u_Textures[ 6], vs_in.TexCoord); break;
		case  7: texColor *= texture(u_Textures[ 7], vs_in.TexCoord); break;
		case  8: texColor *= texture(u_Textures[ 8], vs_in.TexCoord); break;
		case  9: texColor *= texture(u_Textures[ 9], vs_in.TexCoord); break;
		case 10: texColor *= texture(u_Textures[10], vs_in.TexCoord); break;
		case 11: texColor *= texture(u_Textures[11], vs_in.TexCoord); break;
		case 12: texColor *= texture(u_Textures[12], vs_in.TexCoord); break;
		case 13: texColor *= texture(u_Textures[13], vs_in.TexCoord); break;
		case 14: texColor *= texture(u_Textures[14], vs_in.TexCoord); break;
		case 15: texColor *= texture(u_Textures[15], vs_in.TexCoord); break;
	}
    FragColor1 = texColor;
	FragColor2 = vec4(0.9f, 0.2f, 0.3f, 1.0f);
}