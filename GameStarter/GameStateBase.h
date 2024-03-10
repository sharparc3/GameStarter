#pragma once
#include <SDL2/SDL_keycode.h>
#include "Global.h"

class GameStateBase
{
public:
	GameStateBase();
	GameStateBase(GameStateType stateType);
	virtual ~GameStateBase();

	GameStateType GetStateType();

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Exit() = 0;

	virtual void OnKey(int keyCode, bool pressed) = 0;
	virtual void OnMouseClick(int button, bool pressed, int xPos, int yPos) = 0;
	virtual void OnMouseMove(int xPos, int yPos) = 0;
	virtual void OnMouseScroll(float dirX, float dirY, int xPos, int yPos) = 0;

protected:
	GameStateType m_GameStateType;
};