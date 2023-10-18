#version 150 core

in vec3 Position;

out vec4 outColor;

void main()
{
    float x = Position.x;
    float y = Position.y;
    float z = Position.z;
    if (z == 0.0 && (fract(x) == 0.0 || fract(y) == 0.0)) {
        outColor = vec4(1.0);
    } else {
        outColor = vec4(0.0);
    }
}