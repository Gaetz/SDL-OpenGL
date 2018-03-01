#version 150 core

in vec3 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 modelview;

out vec2 coordTexture;

void main()
{
    // Position finale du vertex en 3D
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);

    // Envoi des coordonnées de texture au Fragment Shader
    coordTexture = in_TexCoord0;
}
