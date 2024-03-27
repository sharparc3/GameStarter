#version 330 core 

layout (location = 0) in vec3 vertexPosition; 
layout (location = 1) in vec2 texCoord;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 wvpMatrix;

out vec2 varyingTexCoord;

void main()
{
    varyingTexCoord = texCoord;
    //mat4 wvp = projectionMatrix * viewMatrix * worldMatrix;
    gl_Position = wvpMatrix * vec4(vertexPosition, 1.0); 
    //gl_Position = wvpMatrix * vec4(vertexPosition, 1.0);
    //gl_Position = vec4(vertexPosition, 1.0);
}
