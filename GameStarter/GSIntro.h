#pragma once
#include "GameStateBase.h"

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

	void OnKey(int keyCode, bool pressed) override;
	void OnMouseClick(int button, bool pressed, int xPos, int yPos) override;
	void OnMouseMove(int xPos, int yPos) override;
	void OnMouseScroll(float dirX, float dirY, int xPos, int yPos) override;

private:
};