#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float globalTime;

void main()
{
    vec2 coord = Texcoord;
    if (Texcoord.y >= 0.5) {
        coord.y = 1.0 - Texcoord.y;
    }
    vec4 colKitten = texture(texKitten, coord);
    vec4 colPuppy = texture(texPuppy, Texcoord);
    outColor = vec4(Color, 1.0) * mix(colKitten, colPuppy, globalTime);
}