#version 150 core

in vec2 in_Vertex;
in vec3 in_Color;

out vec3 color;

void main()
{
    // Position finale du vertex
    gl_Position = vec4(in_Vertex, 0.0, 1.0);

    // Envoi de la couleur au Fragment Shader
    color = in_Color;
}
