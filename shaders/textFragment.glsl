#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D foglefont;

void main()
{
    vec4 color = texture(foglefont, Texcoord);
    outColor = color;
}