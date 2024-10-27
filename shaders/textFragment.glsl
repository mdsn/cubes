#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D font;

void main()
{
    vec4 color = texture(font, Texcoord);
    outColor = color;
}