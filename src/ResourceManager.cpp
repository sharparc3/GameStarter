#include "ResourceManager.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Global.h"
#include "Sound.h"

void ResourceManager::LoadMesh(const std::string& name)
{
    std::string path = ResourcesPath::MESH + name;
    if (m_MeshList.count(name) == 0)
    {
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
        if (mesh->LoadMesh(path))
        {
            m_MeshList[name] = mesh;
        }
    }
}

void ResourceManager::LoadShader(const std::string& name)
{
    std::string path_vert = ResourcesPath::SHADER + name + ".vert";
    std::string path_frag = ResourcesPath::SHADER + name + ".frag";

    if (m_ShaderList.count(name) == 0)
    {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>(path_vert, path_frag);
        m_ShaderList[name] = shader;
    }
}

void ResourceManager::LoadTexture(const std::string& name)
{
    std::string path = ResourcesPath::TEXTURE + name;

    if (m_TextureList.count(name) == 0)
    {
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);
        m_TextureList[name] = texture;
    }
}

void ResourceManager::LoadSound(const std::string& name)
{
    std::string path = ResourcesPath::SOUND + name;

    if (m_SoundList.count(name) == 0)
    {
        std::shared_ptr<Sound> sound = std::make_shared<Sound>(path);
        m_SoundList[name] = sound;
    }
}

std::shared_ptr<Mesh> ResourceManager::GetMesh(const std::string& name)
{
    auto it = m_MeshList.find(name);
    if (it != m_MeshList.end()) 
    {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name)
{
    auto it = m_ShaderList.find(name);
    if (it != m_ShaderList.end())
    {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& name)
{
    auto it = m_TextureList.find(name);
    if (it != m_TextureList.end())
    {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Sound> ResourceManager::GetSound(const std::string& name)
{
    auto it = m_SoundList.find(name);
    if (it != m_SoundList.end())
    {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::FreeMesh(const std::string& name)
{
    m_MeshList.erase(name);
}

void ResourceManager::FreeShader(const std::string& name)
{
    m_ShaderList.erase(name);
}

void ResourceManager::FreeTexture(const std::string& name)
{
    m_TextureList.erase(name);
}

void ResourceManager::FreeSound(const std::string& name)
{
    m_SoundList.erase(name);
}

void ResourceManager::FreeAllResources()
{
    m_MeshList.clear();
    m_ShaderList.clear();
    m_TextureList.clear();
    m_SoundList.clear();
}
