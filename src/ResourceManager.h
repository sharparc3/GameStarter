#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <tuple>
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "SingletonDclp.h"

class Mesh;
class Shader;
class Texture;
class Sound;

class ResourceManager : public SingletonDclp<ResourceManager>
{
public:
	void LoadMesh(const std::string& name);
	void LoadShader(const std::string& name);
	void LoadTexture(const std::string& name);
	void LoadSound(const std::string& name);
	void LoadFont(const std::string& name, int size);
	std::shared_ptr<Mesh> GetMesh(const std::string& name);
	std::shared_ptr<Shader> GetShader(const std::string& name);
	std::shared_ptr<Texture> GetTexture(const std::string& name);
	std::shared_ptr<Sound> GetSound(const std::string& name);
	TTF_Font* GetFont(const std::string& name, int size);
	void FreeMesh(const std::string& name);
	void FreeShader(const std::string& name);
	void FreeTexture(const std::string& name);
	void FreeSound(const std::string& name);
	void FreeFont(const std::string& name, int size = 0);
	void FreeAllResources();

private:
	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_MeshList;
	std::unordered_map<std::string, std::shared_ptr<Shader>> m_ShaderList;
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureList;
	std::unordered_map<std::string, std::shared_ptr<Sound>> m_SoundList;
	std::vector<std::tuple<std::string, int, TTF_Font*>> m_FontList;

private:
	void DeleteFontByName(const std::string& name);
	void DeleteFontByNameAndSize(const std::string& name, int size);
};