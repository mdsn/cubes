#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D fogletexture;

void main()
{
    vec4 fogletexture = texture(fogletexture, Texcoord);
    outColor = fogletexture;
}