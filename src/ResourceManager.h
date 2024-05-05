#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "SingletonDclp.h"

class Mesh;
class Shader;
class Texture;
class Sound;
//class TTF_Font;

class ResourceManager : public SingletonDclp<ResourceManager>
{
public:
	void LoadMesh(const std::string& name);
	void LoadShader(const std::string& name);
	void LoadTexture(const std::string& name);
	void LoadSound(const std::string& name);
	//void LoadFont(const std::string& name);
	std::shared_ptr<Mesh> GetMesh(const std::string& name);
	std::shared_ptr<Shader> GetShader(const std::string& name);
	std::shared_ptr<Texture> GetTexture(const std::string& name);
	std::shared_ptr<Sound> GetSound(const std::string& name);
	//std::shared_ptr<TTF_Font> GetFont(const std::string& name);
	void FreeMesh(const std::string& name);
	void FreeShader(const std::string& name);
	void FreeTexture(const std::string& name);
	void FreeSound(const std::string& name);
	void FreeAllResources();

private:
	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_MeshList;
	std::unordered_map<std::string, std::shared_ptr<Shader>> m_ShaderList;
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureList;
	std::unordered_map<std::string, std::shared_ptr<Sound>> m_SoundList;
	//std::unordered_map<std::string, std::shared_ptr<TTF_Font>> m_FontList;
};