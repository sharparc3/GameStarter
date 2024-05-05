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
	GSIntro();
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

private:
	std::shared_ptr<Sprite2D> m_sprite, m_sprite2;
	std::shared_ptr<Renderer> m_renderer;
	std::shared_ptr<Camera> m_camera;
};