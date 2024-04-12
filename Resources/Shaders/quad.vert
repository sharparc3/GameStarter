#version 330 core 

layout (location = 0) in vec3 vertexPosition; 
layout (location = 1) in vec2 texCoord;

uniform mat4 u_mvpMatrix;

out vec2 varyingTexCoord;

void main()
{
    varyingTexCoord = texCoord;
    gl_Position = u_mvpMatrix * vec4(vertexPosition , 1.0); 
}
