#version 150 core

in vec3 color;

out vec4 out_Color;

void main()
{
    // Couleur finale du pixel
    out_Color = vec4(color, 1.0);
}
