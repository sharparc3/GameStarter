#pragma once
#include <string>

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6

namespace ResourcesPath
{
	const std::string TEXTURE = "./Resources/Textures/";
	const std::string MESH = "./Resources/Meshes/";
	const std::string SHADER = "./Resources/Shaders/";
	const std::string SOUND = "./Resources/Sounds/";
	const std::string FONT = "./Resources/Fonts/";
}

enum class GameStateType
{
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY,
	STATE_COUNT
};