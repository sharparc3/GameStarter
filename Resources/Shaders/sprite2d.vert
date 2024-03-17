#version 330 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_uv;

out vec2 v_uv;
out vec4 v_color; // Optional: Add a uniform for setting a base color

uniform mat4 u_mvpMatrix; // Model-View-Projection Matrix

void main() 
{
  // Transform vertex position to clip space using MVP matrix
  gl_Position = u_mvpMatrix * vec4(a_position, 0.0, 1.0);
  // Pass UV coordinates to fragment shader
  v_uv = a_uv;

  // Optional: Set vertex color (if using uniform)
  // v_color = vec4(1.0, 1.0, 1.0, 1.0); // White color (example)
}
