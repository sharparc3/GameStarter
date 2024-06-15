#pragma once
#include <iostream>
#include "GameStateBase.h"

class Renderer;
class Camera;
class Sprite2D;

class GSIntro final : public GameStateBase
{
public:
	using GameStateBase::GameStateBase;
	GSIntro() = delete;
	~GSIntro() override;

	void Init() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void Pause() override;
	void Resume() override;
	void Exit() override;

	void OnKeyDown(const SDL_KeyboardEvent& keyevent) override;
	void OnKeyUp(const SDL_KeyboardEvent& keyevent) override;
	void OnMouseDown(const SDL_MouseButtonEvent& mouseevent) override;
	void OnMouseUp(const SDL_MouseButtonEvent& mouseevent) override;
	void OnMouseMove(const SDL_MouseMotionEvent& motionevent) override;
	void OnMouseScroll(const SDL_MouseWheelEvent& wheelevent) override;
	void OnControllerConnected() override;
	void OnControllerDisconnected() override;
	void OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent) override;
	void OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent) override;
	void OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent) override;
	void OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent) override;
	void OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonEvent) override;
	void OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonEvent) override;
	void OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent) override;
	void OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent) override;
	void ImGuiDraw() override;

private:
	std::shared_ptr<Sprite2D> m_sprite, m_sprite2;
	std::shared_ptr<Renderer> m_renderer;
	std::shared_ptr<Camera> m_camera;
	short joyLeftX, joyLeftY, joyRightX, joyRightY;
};