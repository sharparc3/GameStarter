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

/**
 * @class ResourceManager
 * @brief Manages loading, retrieving, and freeing game resources such as meshes, shaders, textures, sounds, and fonts.
 *
 * This class implements the Singleton pattern to ensure only one instance is used throughout the application.
 */
class ResourceManager : public SingletonDclp<ResourceManager>
{
public:
	/**
	 * @brief Loads a mesh resource from file.
	 * @param name The name of the mesh resource.
	 */
	void LoadMesh(const std::string& name);

	/**
	 * @brief Loads and compiles shader source code from file.
	 * @param name The name of the shader resource (without the extension).
	 * 
	 * A shader consists of one vertex shader and one fragment shader. 
	 * The vertex shader and fragment shader should have the same name with 
	 * corresponding extension .vert and .frag
	 */
	void LoadShader(const std::string& name);

	/**
	 * @brief Loads a texture resource from file.
	 * @param name The name of the texture resource.
	 * 
	 * Supported file extensions: PNG, TGA, JPG, BMP
	 */
	void LoadTexture(const std::string& name);

	/**
	 * @brief Loads a sound resource.
	 * @param name The name of the sound resource.
	 * 
	 * Supported file extensions: WAV, MP3, FLAC, OGG
	 */
	void LoadSound(const std::string& name);

	/**
	 * @brief Loads a font resource.
	 * @param name The name of the font resource.
	 * @param size The size of the font (in pt).
	 * @note This method is currently unused.
	 */
	void LoadFont(const std::string& name, int size);

	/**
	 * @brief Retrieves a loaded mesh resource.
	 * @param name The name of the mesh resource.
	 * @return A shared pointer to the mesh resource.
	 */
	std::shared_ptr<Mesh> GetMesh(const std::string& name);

	/**
	 * @brief Retrieves a loaded shader resource.
	 * @param name The name of the shader resource.
	 * @return A shared pointer to the shader resource.
	 */
	std::shared_ptr<Shader> GetShader(const std::string& name);

	/**
	 * @brief Retrieves a loaded texture resource.
	 * @param name The name of the texture resource.
	 * @return A shared pointer to the texture resource.
	 */
	std::shared_ptr<Texture> GetTexture(const std::string& name);

	/**
	 * @brief Retrieves a loaded sound resource.
	 * @param name The name of the sound resource.
	 * @return A shared pointer to the sound resource.
	 */
	std::shared_ptr<Sound> GetSound(const std::string& name);

	/**
	 * @brief Retrieves a loaded font resource.
	 * @param name The name of the font resource.
	 * @param size The size of the font.
	 * @return A pointer to the font resource.
	 * @note This method is currently unused.
	 */
	TTF_Font* GetFont(const std::string& name, int size);

	/**
	 * @brief Frees a loaded mesh resource.
	 * @param name The name of the mesh resource.
	 */
	void FreeMesh(const std::string& name);

	/**
	 * @brief Frees a loaded shader resource.
	 * @param name The name of the shader resource.
	 */
	void FreeShader(const std::string& name);

	/**
	 * @brief Frees a loaded texture resource.
	 * @param name The name of the texture resource.
	 */
	void FreeTexture(const std::string& name);

	/**
	 * @brief Frees a loaded sound resource.
	 * @param name The name of the sound resource.
	 */
	void FreeSound(const std::string& name);

	/**
	 * @brief Frees a loaded font resource.
	 * @param name The name of the font resource.
	 * @param size The size of the font. Defaults to 0.
	 * @note This method is currently unused.
	 */
	void FreeFont(const std::string& name, int size = 0);

	/**
	 * @brief Frees all loaded resources.
	 */
	void FreeAllResources();

private:
	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_MeshList;				///< List of loaded meshes.
	std::unordered_map<std::string, std::shared_ptr<Shader>> m_ShaderList;			///< List of loaded shaders.
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureList;		///< List of loaded textures.
	std::unordered_map<std::string, std::shared_ptr<Sound>> m_SoundList;			///< List of loaded sounds.
	std::vector<std::tuple<std::string, int, TTF_Font*>> m_FontList;				///< List of loaded fonts. Currently unused.

private:
	void DeleteFontByName(const std::string& name);
	void DeleteFontByNameAndSize(const std::string& name, int size);
};

/**
 * @def RESOURCE
 * @brief Macro to get the singleton instance of the ResourceManager.
 */
#define RESOURCE() ResourceManager::GetInstance()