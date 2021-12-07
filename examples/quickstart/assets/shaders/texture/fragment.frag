#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec4 Color;
    vec2 TexCoord;
    float v_TexIndex ;
} vs_in;
uniform sampler2D u_Textures[2];
void main()
{
    vec4 texColor = vs_in.Color;
	texColor *= texture(u_Textures[0], vs_in.TexCoord);
	// switch(int(vs_in.v_TexIndex))
	// {
	// 	case  0: texColor *= texture(u_Textures[ 0], vs_in.TexCoord); break;
	// 	case  1: texColor *= texture(u_Textures[ 1], vs_in.TexCoord); break;
	// 	case  2: texColor *= texture(u_Textures[ 2], vs_in.TexCoord); break;
	// 	case  3: texColor *= texture(u_Textures[ 3], vs_in.TexCoord); break;
	// 	case  4: texColor *= texture(u_Textures[ 4], vs_in.TexCoord); break;
	// 	case  5: texColor *= texture(u_Textures[ 5], vs_in.TexCoord); break;
	// 	case  6: texColor *= texture(u_Textures[ 6], vs_in.TexCoord); break;
	// 	case  7: texColor *= texture(u_Textures[ 7], vs_in.TexCoord); break;
	// 	case  8: texColor *= texture(u_Textures[ 8], vs_in.TexCoord); break;
	// 	case  9: texColor *= texture(u_Textures[ 9], vs_in.TexCoord); break;
	// 	case 10: texColor *= texture(u_Textures[10], vs_in.TexCoord); break;
	// 	case 11: texColor *= texture(u_Textures[11], vs_in.TexCoord); break;
	// 	case 12: texColor *= texture(u_Textures[12], vs_in.TexCoord); break;
	// 	case 13: texColor *= texture(u_Textures[13], vs_in.TexCoord); break;
	// 	case 14: texColor *= texture(u_Textures[14], vs_in.TexCoord); break;
	// 	case 15: texColor *= texture(u_Textures[15], vs_in.TexCoord); break;
	// 	case 16: texColor *= texture(u_Textures[16], vs_in.TexCoord); break;
	// 	case 17: texColor *= texture(u_Textures[17], vs_in.TexCoord); break;
	// 	case 18: texColor *= texture(u_Textures[18], vs_in.TexCoord); break;
	// 	case 19: texColor *= texture(u_Textures[19], vs_in.TexCoord); break;
	// 	case 20: texColor *= texture(u_Textures[20], vs_in.TexCoord); break;
	// 	case 21: texColor *= texture(u_Textures[21], vs_in.TexCoord); break;
	// 	case 22: texColor *= texture(u_Textures[22], vs_in.TexCoord); break;
	// 	case 23: texColor *= texture(u_Textures[23], vs_in.TexCoord); break;
	// 	case 24: texColor *= texture(u_Textures[24], vs_in.TexCoord); break;
	// 	case 25: texColor *= texture(u_Textures[25], vs_in.TexCoord); break;
	// 	case 26: texColor *= texture(u_Textures[26], vs_in.TexCoord); break;
	// 	case 27: texColor *= texture(u_Textures[27], vs_in.TexCoord); break;
	// 	case 28: texColor *= texture(u_Textures[28], vs_in.TexCoord); break;
	// 	case 29: texColor *= texture(u_Textures[29], vs_in.TexCoord); break;
	// 	case 30: texColor *= texture(u_Textures[30], vs_in.TexCoord); break;
	// 	case 31: texColor *= texture(u_Textures[31], vs_in.TexCoord); break;
	// }
    FragColor = texColor;
}