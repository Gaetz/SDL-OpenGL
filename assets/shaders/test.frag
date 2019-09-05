#version 330

in vec2 TexCoords;

uniform sampler2D image;

out vec4 color;

void main ()
{
    vec4 texel = texture(image, TexCoords);
    color = texel;
}