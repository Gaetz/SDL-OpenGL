#version 150 core

in vec3 in_Vertex;
in vec3 in_Color;

uniform mat4 projection;
uniform mat4 modelview;

out vec3 color;

void main()
{
    // Position finale du vertex en 3D
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);

    // Envoi de la couleur au Fragment Shader
    color = in_Color;
}
