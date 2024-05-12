#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <glm/glm.hpp>
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "SoundPlayer.h"

void Init();
void Draw();
void Update(float deltaTime);
void OnKeyDown(const SDL_KeyboardEvent& keyevent);
void OnKeyUp(const SDL_KeyboardEvent& keyevent);
void OnMouseDown(const SDL_MouseButtonEvent& mouseevent);
void OnMouseUp(const SDL_MouseButtonEvent& mouseevent);
void OnMouseMove(const SDL_MouseMotionEvent& motionevent);
void OnMouseScroll(const SDL_MouseWheelEvent& wheelevent);
void OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonevent);
void OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonevent);
void OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent);
void OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent);
void OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent);
void OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent);
void OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent);
void OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent);

void OnControllerConnected();
void OnControllerDisconnected();

void CleanUp(SDL_GLContext glContext, SDL_Window* window)
{
    // Destroy the OpenGL context and window
    if (glContext)
    {
        SDL_GL_DeleteContext(glContext);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }

    // free singleton classes
    GameStateMachine::GetInstance()->CleanUp();
    GameStateMachine::Destruct();
    ResourceManager::GetInstance()->FreeAllResources();
    ResourceManager::Destruct();
    SoundPlayer::GetInstance()->Deinit();
    SoundPlayer::Destruct();

    // Quit SDL
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL video: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Failed to initialize SDL audio: " << SDL_GetError() << std::endl;
        return -1;
    }

    // init sdl ttf
    if (TTF_Init() < 0)
    {
        std::cerr << "Failed to initialize SDL ttf: " << SDL_GetError() << std::endl;
    }

    // init game controller subsystem
    if (SDL_Init(SDL_INIT_GAMECONTROLLER))
    {
        std::cerr << "SDL game controller subsystem failed to initialize";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("GLAD Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen::WIDTH, Screen::HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create an OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    
    if (!glContext)
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Enable VSync (Swap Interval = 1)
    //if (SDL_GL_SetSwapInterval(1) < 0)
    //{
    //    SDL_Log("Failed to set VSync: %s", SDL_GetError());
    //}

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Check if GLAD initialized successfully
    std::cout << "GLAD initialized successfully!" << std::endl;
    std::cout << "OpenGL version: " << (char*)glGetString(GL_VERSION) << std::endl;

    // Init game state machine
    Init();

    // Main loop

    auto lastTime = std::chrono::steady_clock::now();
    auto curTime = std::chrono::steady_clock::now();
    std::chrono::duration<float, std::milli> durationMicro;

    float deltaTime;
    SDL_Event event;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    int numJoystick = 0;

    std::vector<SDL_GameController*> controllerArray;
    numJoystick = SDL_NumJoysticks();

    while (GameStateMachine::GetInstance()->IsRunning())
    {
        // TODO: event queue
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                // mouse movement
                OnMouseMove(event.motion);
                break;

            case SDL_MOUSEBUTTONDOWN:
                // mouse button pressed
                OnMouseDown(event.button);
                break;

            case SDL_MOUSEBUTTONUP:
                // mouse button released
                OnMouseUp(event.button);
                break;

            case SDL_KEYDOWN:
                // key pressed
                OnKeyDown(event.key);
                break;

            case SDL_KEYUP:
                // key released
                OnKeyUp(event.key);
                break;

            case SDL_QUIT:
                GameStateMachine::GetInstance()->Exit();
                break;

            case SDL_CONTROLLERDEVICEADDED:
                if (SDL_IsGameController(event.cdevice.which)) 
                {
                    SDL_GameController* controller = SDL_GameControllerOpen(event.cdevice.which);
                    if (controller) 
                    {
                        controllerArray.push_back(controller);
                    }
                }
                OnControllerConnected();
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
            {
                int controllerID = event.cdevice.which;
                // Find the controller
                auto it = std::find_if(controllerArray.begin(), controllerArray.end(),
                    [controllerID](SDL_GameController* controller)
                    {
                        return SDL_GameControllerFromInstanceID(controllerID) == controller;
                    });
                // Check if controller found
                if (it != controllerArray.end())
                {
                    // Close the controller before removal
                    SDL_GameControllerClose(*it);
                    // Remove the controller
                    controllerArray.erase(it);
                }
                OnControllerDisconnected();
            }
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                OnControllerButtonDown(event.cbutton);
                break;

            case SDL_CONTROLLERBUTTONUP:
                OnControllerButtonUp(event.cbutton);
                break;

            case SDL_CONTROLLERAXISMOTION:
            {
                switch (event.caxis.axis)
                {
                case SDL_CONTROLLER_AXIS_LEFTX:
                    OnControllerLeftJoystickMotionX(event.caxis);
                    break;

                case SDL_CONTROLLER_AXIS_LEFTY:
                    OnControllerLeftJoystickMotionY(event.caxis);
                    break;

                case SDL_CONTROLLER_AXIS_RIGHTX:
                    OnControllerRightJoystickMotionX(event.caxis);
                    break;

                case SDL_CONTROLLER_AXIS_RIGHTY:
                    OnControllerRightJoystickMotionY(event.caxis);
                    break;

                case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                    OnLeftTriggerMotion(event.caxis);
                    break;

                case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                    OnRightTriggerMotion(event.caxis);
                    break;
                }
            }
                break;

            default:
                break;
            }
        }
        auto curTime = std::chrono::steady_clock::now();
        durationMicro = curTime - lastTime;

        // Limit the FPS
        if (durationMicro.count() <= 1000.f / FPS)
        {
            //// some dirty hack to reduce CPU usage
            //float expected = 1000.f / FPS;
            //if (durationMicro.count() < expected / 2)
            //{
            //    auto amount = static_cast<Uint32>((expected - durationMicro.count()) / 2);
            //    SDL_Delay(static_cast<Uint32>((expected - durationMicro.count()) / 2));
            //}
            continue;
        }
        deltaTime = durationMicro.count() / 1000;
        lastTime = curTime;
        
        // BuildBuffer using OpenGL here
        Update(deltaTime);
        Draw();
        //std::cout << 1.f / deltaTime << "\n";
        SDL_GL_SwapWindow(window);
    }

    CleanUp(glContext, window);

    return 0;
}

void Init()
{
    ResourceManager::Construct();
    GameStateMachine::Construct();
    SoundPlayer::Construct();
    SoundPlayer::GetInstance()->Init();
    GameStateMachine::GetInstance()->Init();
    GameStateMachine::GetInstance()->PushState(GameStateType::STATE_INTRO);

    
    // enable blend for transparent texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->Draw();
    }
}

void Update(float deltaTime)
{
    // update state change
    GameStateMachine::GetInstance()->Update();
    // get current game state and update
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->Update(deltaTime);
    }
}

void OnKeyDown(const SDL_KeyboardEvent& keyevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnKeyDown(keyevent);
    }
}

void OnKeyUp(const SDL_KeyboardEvent& keyevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnKeyUp(keyevent);
    }
}

void OnMouseDown(const SDL_MouseButtonEvent& mouseevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseDown(mouseevent);
    }
}

void OnMouseUp(const SDL_MouseButtonEvent& mouseevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseUp(mouseevent);
    }
}

void OnMouseMove(const SDL_MouseMotionEvent& motionevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseMove(motionevent);
    }
}

void OnMouseScroll(const SDL_MouseWheelEvent& wheelevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseScroll(wheelevent);
    }
}

void OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerButtonDown(buttonevent);
    }
}

void OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerButtonUp(buttonevent);
    }
}

void OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerLeftJoystickMotionX(joystickEvent);
    }
}

void OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerLeftJoystickMotionY(joystickEvent);
    }
}

void OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerRightJoystickMotionX(joystickEvent);
    }
}

void OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerRightJoystickMotionY(joystickEvent);
    }
}

void OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnLeftTriggerMotion(triggerEvent);
    }
}

void OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnRightTriggerMotion(triggerEvent);
    }
}

void OnControllerConnected()
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerConnected();
    }
}

void OnControllerDisconnected()
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerDisconnected();
    }
}
