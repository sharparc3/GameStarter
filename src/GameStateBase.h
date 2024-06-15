#pragma once
#include <SDL2/SDL_events.h>
#include "Config.h"

class GameStateBase
{
public:
	GameStateBase() = delete;
	GameStateBase(GameStateType stateType);
	virtual ~GameStateBase();

	GameStateType GetStateType() const;

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
	virtual void OnControllerConnected() = 0;
	virtual void OnControllerDisconnected() = 0;
	virtual void OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent) = 0;
	virtual void OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent) = 0;
	virtual void OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent) = 0;
	virtual void OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent) = 0;
	virtual void OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonEvent) = 0;
	virtual void OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonEvent) = 0;
	virtual void OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent) = 0;
	virtual void OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent) = 0;
	virtual void ImGuiDraw();

protected:
	GameStateType m_GameStateType;

};