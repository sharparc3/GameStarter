#include "GameStateMachine.h"
#include "GameStateBase.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include <iostream>

void GameStateMachine::Init()
{
    m_pActiveState = nullptr;
    m_pNextState = nullptr;
    m_exit = false;
}

void GameStateMachine::CleanUp()
{
    m_pActiveState.reset();
    m_pNextState.reset();
    m_pActiveState = m_pNextState = nullptr;
}

void GameStateMachine::PushState(GameStateType stateType)
{
    auto newState = CreateGameState(stateType);
    if (m_stateStack.empty())
    {
        m_stateStack.push(newState);
        m_pActiveState = newState;
        m_pActiveState->Init();
    }
    else
    {
        m_stateStack.push(newState);
        m_pNextState = newState;
    }
}

void GameStateMachine::PopState()
{
    if (m_stateStack.empty())
    {
        m_exit = true;
        return;
    }

    m_pActiveState->Exit();
    m_stateStack.pop();
    if (m_stateStack.empty())
    {
        m_pActiveState = nullptr;
    }
    else
    {
        m_pActiveState = m_stateStack.top();
        m_pActiveState->Resume();
    }
}

void GameStateMachine::Update()
{
    if (m_pNextState)
    {
        m_pActiveState->Pause();
        m_pActiveState = m_pNextState;
        m_pActiveState->Init();
        m_pNextState = nullptr;
    }
    if (m_exit)
    {
        while (!m_stateStack.empty())
        {
            m_stateStack.pop(); 
        }
    }
}

void GameStateMachine::Exit()
{
    m_exit = true;
}

bool GameStateMachine::HasState()
{
    if (m_pActiveState) return true;
    return false;
}

std::shared_ptr<GameStateBase> GameStateMachine::GetCurrentState()
{
    return m_pActiveState;
}

std::shared_ptr<GameStateBase> CreateGameState(GameStateType gameStateType)
{
    std::shared_ptr<GameStateBase> newState;
    switch (gameStateType)
    {
    case GameStateType::STATE_INTRO:
        newState = std::make_shared<GSIntro>(gameStateType);
        break;
    case GameStateType::STATE_MENU:
        newState = std::make_shared<GSMenu>(gameStateType);
        break;
    case GameStateType::STATE_PLAY:
        newState = std::make_shared<GSPlay>(gameStateType);
        break;
    default:
        std::cerr << "Unknown state type: " << (int)gameStateType << "\n";
        break;
    }
    return newState;
}
