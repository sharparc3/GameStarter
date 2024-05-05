#version 330 core

layout (location = 0) in vec3 vertexPosition;  // Vertex location
layout (location = 1) in vec2 texCoord;

uniform mat4 u_mvpMatrix;

uniform float currentFrame;
uniform float frameCount;

out vec2 v_texCoord;  // Output texture coordinate

void main() 
{
    // Calculate final vertex position
    gl_Position = u_mvpMatrix * vec4(vertexPosition, 1.0);

    // Calculate texture coordinates for the current frame
    float frameWidth = 1.0 / frameCount;
    float frameX = mod(currentFrame, frameCount) * frameWidth;  

    // Assume texture coordinates lie within a single row of spritesheet
    v_texCoord = vec2(frameX + frameWidth * texCoord.x, texCoord.y);
}
