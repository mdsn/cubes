#version 150 core

in vec3 Position;

out vec4 outColor;

void main()
{
    if (mod(Position.x, 1.1) < 1. ||
        mod(Position.y, 1.1) < 1.) {
        outColor = vec4(vec3(1.0), 0.0);
    } else {
        outColor = vec4(0.0);
    }
}