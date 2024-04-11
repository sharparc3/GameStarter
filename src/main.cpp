#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <chrono>
#include <glm/glm.hpp>
#include "GameStateMachine.h"
#include "ResourceManager.h"

void Init();
void Draw();
void Update(float deltaTime);
void OnKeyDown(const SDL_KeyboardEvent& keyevent);
void OnKeyUp(const SDL_KeyboardEvent& keyevent);
void OnMouseDown(const SDL_MouseButtonEvent& mouseevent);
void OnMouseUp(const SDL_MouseButtonEvent& mouseevent);
void OnMouseMove(const SDL_MouseMotionEvent& motionevent);
void OnMouseScroll(const SDL_MouseWheelEvent& wheelevent);

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

    // Free game state machine
    GameStateMachine::Destruct();
    // Quit SDL
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
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
        std::cout << 1.f / deltaTime << "\n";
        SDL_GL_SwapWindow(window);
    }

    GameStateMachine::GetInstance()->CleanUp();
    GameStateMachine::Destruct();
    ResourceManager::GetInstance()->FreeAllResources();
    ResourceManager::Destruct();
    CleanUp(glContext, window);

    return 0;
}

void Init()
{
    ResourceManager::Construct();
    GameStateMachine::Construct();
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
