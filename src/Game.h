#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <chrono>
#include <glm/glm.hpp>
#include "SingletonDclp.h"

class Game : public SingletonDclp<Game>
{
public:
	int Init();
	void CleanUp();
	void Run();

private:
	SDL_Window* m_pWindow;
	SDL_GLContext* m_pGlContext;
};