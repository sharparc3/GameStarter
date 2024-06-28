#include "GSIntro.h"

#include <random>
#include <chrono>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include "Renderer.h"
#include "Camera.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "Sprite2D.h"
#include "Game.h"
#include "SoundPlayer.h"
#include "Sound.h"
#include "Logger.h"

GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{

}

void GSIntro::Update(float deltaTime)
{

}

void GSIntro::Draw()
{

}

void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}

void GSIntro::Exit()
{
}

void GSIntro::OnKeyDown(const SDL_KeyboardEvent& keyevent)
{
}

void GSIntro::OnKeyUp(const SDL_KeyboardEvent& keyevent)
{
    auto gameIns = Game::GetInstance();
    switch (keyevent.keysym.sym)
    {
    case SDLK_w:

        break;
    case SDLK_a:

        break;
    case SDLK_s:

        break;
    case SDLK_d:

        break;
    case SDLK_SPACE:

        break;
    case SDLK_ESCAPE:

        break;
    default:
        break;
    }
}

void GSIntro::OnMouseDown(const SDL_MouseButtonEvent& mouseevent)
{
}

void GSIntro::OnMouseUp(const SDL_MouseButtonEvent& mouseevent)
{
    switch (mouseevent.button)
    {
    case SDL_BUTTON_LEFT:

        break;
    case SDL_BUTTON_RIGHT:

        break;
    default:
        break;
    }
}

void GSIntro::OnMouseMove(const SDL_MouseMotionEvent& motionevent)
{
}

void GSIntro::OnMouseScroll(const SDL_MouseWheelEvent& wheelevent)
{
}

void GSIntro::OnControllerConnected()
{
    std::cout << "A controller connected\n";
}

void GSIntro::OnControllerDisconnected()
{
    std::cout << "A controller disconnected\n";
}

void GSIntro::OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    joyLeftX = joystickEvent.value;
    glm::vec2 directionVec(joyLeftX, joyLeftY);
    directionVec = glm::normalize(directionVec);

}

void GSIntro::OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    joyLeftY = joystickEvent.value;
    glm::vec2 directionVec(joyLeftX, joyLeftY);
    directionVec = glm::normalize(directionVec);

}

void GSIntro::OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    joyRightX = joystickEvent.value;
    glm::vec2 directionVec(joyRightX, joyRightY);
    directionVec = glm::normalize(directionVec);

}

void GSIntro::OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    joyRightY = joystickEvent.value;
    glm::vec2 directionVec(joyRightX, joyRightY);
    directionVec = glm::normalize(directionVec);

}

void GSIntro::OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonEvent)
{
    switch (buttonEvent.button)
    {
    case SDL_CONTROLLER_BUTTON_A:
        // Handle A button press

        break;
    case SDL_CONTROLLER_BUTTON_B:
        // Handle B button press

        break;
    case SDL_CONTROLLER_BUTTON_X:
        // Handle X button press

        break;
    case SDL_CONTROLLER_BUTTON_Y:
        // Handle Y button press

        break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        // Handle left bumper press

        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        // Handle right bumper press

        break;
    case SDL_CONTROLLER_BUTTON_BACK:
        // Handle back button press

        break;
    case SDL_CONTROLLER_BUTTON_START:
        // Handle start button press

        break;
    case SDL_CONTROLLER_BUTTON_GUIDE:
        // Handle guide button press

        break;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        // Handle left stick click

        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        // Handle right stick click

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        // Handle D-pad up press

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        // Handle D-pad down press

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        // Handle D-pad left press

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        // Handle D-pad right press

        break;

    default:
        break;
    }

}

void GSIntro::OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonEvent)
{
    switch (buttonEvent.button)
    {
    case SDL_CONTROLLER_BUTTON_A:
        // Handle A button up

        break;
    case SDL_CONTROLLER_BUTTON_B:
        // Handle B button up

        break;
    case SDL_CONTROLLER_BUTTON_X:
        // Handle X button up

        break;
    case SDL_CONTROLLER_BUTTON_Y:
        // Handle Y button up

        break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        // Handle left bumper up

        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        // Handle right bumper up

        break;
    case SDL_CONTROLLER_BUTTON_BACK:
        // Handle back button up

        break;
    case SDL_CONTROLLER_BUTTON_START:
        // Handle start button up

        break;
    case SDL_CONTROLLER_BUTTON_GUIDE:
        // Handle guide button up

        break;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        // Handle left stick up

        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        // Handle right stick up

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        // Handle D-pad up up

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        // Handle D-pad down up

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        // Handle D-pad left up

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        // Handle D-pad right up

        break;

    default:
        // Handle other button up or unknown buttons
        break;
    }

}

void GSIntro::OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    short value = triggerEvent.value;
    float normalized = value >= 0 ? (float)value / 32767 : (float)value / 32768;

}

void GSIntro::OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    short value = triggerEvent.value;
    float normalized = value >= 0 ? (float)value / 32767 : (float)value / 32768;

}

void GSIntro::ImGuiDraw()
{

}
