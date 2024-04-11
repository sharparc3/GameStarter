#pragma once
#include <string>

#define FPS 60

namespace Screen
{
	const int WIDTH = 960;
	const int HEIGHT = 540;
}

namespace ResourcesPath
{
	const std::string TEXTURE = "./Resources/Textures/";
	const std::string MESH = "./Resources/Meshes/";
	const std::string SHADER = "./Resources/Shaders/";
}

enum class GameStateType
{
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY,
	UNDEFINED
};
