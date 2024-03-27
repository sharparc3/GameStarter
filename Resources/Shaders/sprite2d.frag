#version 330 core 

in vec2 varyingTexCoord;

out vec4 fragColor;

uniform sampler2D spriteTexture;

void main()
{
    fragColor = texture(spriteTexture, varyingTexCoord);
    //fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
