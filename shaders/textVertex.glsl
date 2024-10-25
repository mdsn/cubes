#version 150 core
in vec4 vertex; // (vec2 xy, vec2 uv)

out vec2 Texcoord;

uniform mat4 proj;

void main()
{
    Texcoord = vertex.zw;
    gl_Position = proj * vec4(vertex.xy, 0.0, 1.0);
}
