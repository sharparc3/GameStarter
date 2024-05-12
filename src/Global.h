#pragma once
#include <string>

#define FPS 60
#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6

namespace Screen
{
	const int WIDTH = 1600;
	const int HEIGHT = 900;
}

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
	UNDEFINED
};
