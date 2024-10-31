#version 150 core

in vec2 texcoord;
in vec3 position;
in float intensity;

out vec2 Texcoord;
out float Intensity;

uniform mat4 view;
uniform mat4 proj;

void main()
{
    Texcoord = texcoord;
    Intensity = intensity;
    gl_Position = proj * view * vec4(position, 1.0);
}