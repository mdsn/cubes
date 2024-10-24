#version 150 core

in vec2 texcoord;
in vec3 position;

out vec2 Texcoord;

uniform mat4 view;
uniform mat4 proj;

void main()
{
    Texcoord = texcoord;
    gl_Position = proj * view * vec4(position, 1.0);
}