#version 330 core

in vec2 TexCoords;

uniform sampler2D image;
uniform vec3 spriteColor;

out vec4 color;

void main()
{    
    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}  