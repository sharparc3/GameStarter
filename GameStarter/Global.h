#pragma once
#include <string>
#include <SDL2/SDL_mouse.h>

namespace ResourcesPath
{
	const std::string TEXTURE = "/Data/Resources/Textures/";
	const std::string MODEL = "/Data/Resources/Models/";
}

enum class GameStateType
{
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY,
	UNDEFINED
};
