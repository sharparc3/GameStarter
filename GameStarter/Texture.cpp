#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture(const std::string& filePath) 
{
    m_iTextureID = 0;
    LoadImage(filePath);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_iTextureID);
}

void Texture::Bind(GLuint textureUnit) 
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_iTextureID);
}

void Texture::SetFilter(TextureFilterMode mode)
{
    glBindTexture(GL_TEXTURE_2D, m_iTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetTextureID() const
{
    return m_iTextureID;
}

void Texture::LoadImage(const std::string& filePath) 
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (data) 
    {
        GLenum format;
        format = GL_RGBA;
        if (nrChannels == 1)
        {
            format = GL_RED;
        }
        else 
        if (nrChannels == 3)
        {
            format = GL_RGB;
        }
        glGenTextures(1, &m_iTextureID);
        glBindTexture(GL_TEXTURE_2D, m_iTextureID);

        // Set texture parameters 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Load image data into the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "glTexImage2D error: " << error << std::endl;
        }

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else 
    {
        std::cerr << "ERROR: Failed to load texture: " << filePath << std::endl;
    }

    stbi_image_free(data);
}
