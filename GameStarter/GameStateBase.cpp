#include "GameStateBase.h"
#include "Global.h"

GameStateBase::GameStateBase()
{
	m_GameStateType = GameStateType::UNDEFINED;
}

GameStateBase::GameStateBase(GameStateType stateType) : m_GameStateType(stateType)
{
}

GameStateBase::~GameStateBase()
{
}

GameStateType GameStateBase::GetStateType()
{
	return m_GameStateType;
}
