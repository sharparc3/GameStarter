#version 330 core

in vec2 v_texCoord;

out vec4 FragColor;

uniform sampler2D spriteSheet; 

void main() 
{
    FragColor = texture(spriteSheet, v_texCoord); 
}
