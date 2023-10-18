#version 150 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float time;

void main()
{
    vec2 coord = Texcoord;
    if (Texcoord.y >= 0.5) {
        coord.y = 1.0 - Texcoord.y;
    }
    vec4 colKitten = texture(texKitten, coord);
    vec4 colPuppy = texture(texPuppy, Texcoord);
    outColor = mix(colKitten, colPuppy, time);
}