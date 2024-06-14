#include "GameStateBase.h"
#include "Global.h"

GameStateBase::GameStateBase(GameStateType stateType) : m_GameStateType(stateType)
{
}

GameStateBase::~GameStateBase()
{
}

GameStateType GameStateBase::GetStateType() const
{
	return m_GameStateType;
}
