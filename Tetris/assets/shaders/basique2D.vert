#version 150 core

in vec2 in_Vertex;

void main()
{
    // Position finale du vertex
    gl_Position = vec4(in_Vertex, 0.0, 1.0);
}
