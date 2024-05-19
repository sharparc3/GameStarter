#pragma once
#include <stack>
#include <memory>
#include "SingletonDclp.h"
#include "Global.h"
#include "GameStateBase.h"

class GameStateBase;

class GameStateMachine final : public SingletonDclp<GameStateMachine>
{
public:
	void Init();
	void CleanUp();
	void PushState(GameStateType stateType);
	void PopState();
	void Update();
	void Exit();
	bool HasState();
	std::shared_ptr<GameStateBase> GetCurrentState();
	inline bool IsRunning() const { return !m_exit; };

private:
	std::stack<std::shared_ptr<GameStateBase>> m_stateStack;
	std::shared_ptr<GameStateBase> m_pActiveState;
	std::shared_ptr<GameStateBase> m_pNextState;
	bool m_exit;

};

std::shared_ptr<GameStateBase> CreateGameState(GameStateType gameStateType);