#pragma once
#include <SDL2/SDL_events.h>
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

	virtual void OnKeyDown(const SDL_KeyboardEvent& keyevent) = 0;
	virtual void OnKeyUp(const SDL_KeyboardEvent& keyevent) = 0;
	virtual void OnMouseDown(const SDL_MouseButtonEvent& mouseevent) = 0;
	virtual void OnMouseUp(const SDL_MouseButtonEvent& mouseevent) = 0;
	virtual void OnMouseMove(const SDL_MouseMotionEvent& motionevent) = 0;
	virtual void OnMouseScroll(const SDL_MouseWheelEvent& wheelevent) = 0;

protected:
	GameStateType m_GameStateType;
};