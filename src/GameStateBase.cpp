#include "GameStateBase.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include "Config.h"

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

void GameStateBase::ImGuiDraw()
{

}
