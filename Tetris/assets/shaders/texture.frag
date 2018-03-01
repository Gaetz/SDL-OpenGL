#version 150 core

in vec2 coordTexture;

uniform sampler2D texture;

out vec4 out_Color;

void main()
{
    // Couleur du pixel
    out_Color = texture(texture, coordTexture);
}
