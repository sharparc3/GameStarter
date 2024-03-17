#version 330 core

out vec4 FragColor;

in vec2 v_uv;
in vec4 v_color; // Optional: Input vertex color (if used)

uniform sampler2D u_texture; // Texture sampler

void main() 
{
  // Sample the texture at the provided UV coordinates
  vec4 textureColor = texture(u_texture, v_uv);

  // Optional: Multiply vertex color with texture color for tinting
  // FragColor = textureColor * v_color;

  // Set the final fragment color (or use previous line for tinting)
  FragColor = textureColor;
}
