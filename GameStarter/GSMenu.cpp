#include "GSMenu.h"

GSMenu::GSMenu()
{
}

GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	std::cout << "Switched to menu state.\n";
}

void GSMenu::Update(float deltaTime)
{
}

void GSMenu::Draw()
{
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::Exit()
{
}

void GSMenu::OnKeyDown(const SDL_KeyboardEvent& keyevent)
{
}

void GSMenu::OnKeyUp(const SDL_KeyboardEvent& keyevent)
{
}

void GSMenu::OnMouseDown(const SDL_MouseButtonEvent& mouseevent)
{
}

void GSMenu::OnMouseUp(const SDL_MouseButtonEvent& mouseevent)
{
	switch (mouseevent.button)
	{
	case SDL_BUTTON_RIGHT:
		std::cout << "State popped: Menu.\n";
		GameStateMachine::GetInstance()->PopState();
		break;
	default:
		break;
	}
}

void GSMenu::OnMouseMove(const SDL_MouseMotionEvent& motionevent)
{
}

void GSMenu::OnMouseScroll(const SDL_MouseWheelEvent& wheelevent)
{
}

