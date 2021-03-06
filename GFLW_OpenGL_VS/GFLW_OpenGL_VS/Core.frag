#version 330 core

in vec4 Color;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main()
{
	color = texture(ourTexture1, TexCoord);
}