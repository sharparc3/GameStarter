#version 330 core

layout (location = 0) in vec3 vertexPosition;  // Vertex location

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float currentFrame;
uniform float frameCount;

out vec2 texCoord;  // Output texture coordinate

void main() 
{
    // Calculate final vertex position
    gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(vertexPosition, 1.0);

    // Calculate texture coordinates for the current frame
    float frameWidth = 1.0 / frameCount;
    float frameX = mod(currentFrame, frameCount) * frameWidth;  

    // Assume texture coordinates lie within a single row of spritesheet
    texCoord = vec2(frameX + frameWidth * vertexPosition.x, vertexPosition.y);
}
