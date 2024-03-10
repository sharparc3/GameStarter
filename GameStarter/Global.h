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
	STATE_PLAY
};

namespace MouseButton
{
	const int LEFT = SDL_BUTTON_LEFT;
	const int RIGHT = SDL_BUTTON_RIGHT;
	const int MIDDLE = SDL_BUTTON_MIDDLE;
	const int BACK = SDL_BUTTON_X1;
	const int FORWARD = SDL_BUTTON_X2;
}