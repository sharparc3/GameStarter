#include "Game.h"

#if defined(_WIN64) || defined(_WIN32)
#include <Windows.h>
#endif // _WIN64 || _WIN32 

#include <glad/glad.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Logger.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "SoundPlayer.h"


int Game::InitSDL()
{
    // init SDL video
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        LogError("SDL video initialization failed, %s", SDL_GetError());
        SDL_ClearError();
        return 1;
    }

    // init SDL audio
    if (SDL_Init(SDL_INIT_AUDIO))
    {
        LogError("SDL audio initialization failed, %s", SDL_GetError());
        SDL_ClearError();
        return 1;
    }

    // init SDL ttf
    if (TTF_Init())
    {
        LogError("SDL ttf initialization failed, %s", SDL_GetError());
        SDL_ClearError();
        return 1;
    }

    // init SDL game controller subsystem
    if (SDL_Init(SDL_INIT_GAMECONTROLLER))
    {
        LogError("SDL controller subsystem initialization failed, %s", SDL_GetError());
        SDL_ClearError();
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    return 0;
}

int Game::InitOpenGL()
{
    // Create an SDL window
    m_pWindow = SDL_CreateWindow("SDL OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!m_pWindow)
    {
        LogError("Failed to create SDL window, %s", SDL_GetError());
        SDL_ClearError();
        return -1;
    }

    // Create an OpenGL context
    m_pGLContext = SDL_GL_CreateContext(m_pWindow);

    if (!m_pGLContext)
    {
        LogError("Failed to create OpenGL context, %s", SDL_GetError());
        SDL_ClearError();
        SDL_DestroyWindow(m_pWindow);
        return -1;
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        LogError("Failed to initialize GLAD");
        SDL_GL_DeleteContext(m_pGLContext);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        return -1;
    }

    // Set the initial viewport to match the window size
    SDL_GetWindowSize(m_pWindow, &m_ScreenWidth, &m_ScreenHeight);
    glViewport(0, 0, m_ScreenWidth, m_ScreenHeight);

    LogSuccess("GLAD initialized successfully!");
    LogSuccess("OpenGL version: %s", (char*)glGetString(GL_VERSION));

    // enable blend for transparent texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

int Game::GameInit()
{
    // start ticking
    m_lastTime = m_currentTime = std::chrono::steady_clock::now();

    // default clear color is white
    SetClearColor();

    // default FPS limit is 60
    m_LimitFPS = 60.f;

    // enable VSync by default
    SetVSync(1);

    // ignore Windows scaling
    SetIgnoreWindowsScaling();

    // set window title
    SetWindowTitle("GAME");

    // set window resolution
    m_ScreenWidth = 1600;
    m_ScreenHeight = 900;
    SetWindowResolution(m_ScreenWidth, m_ScreenHeight);

    m_GameRunning = true;

    // init singleton classes
    ResourceManager::Construct();
    GameStateMachine::Construct();
    SoundPlayer::Construct();
    SoundPlayer::GetInstance()->Init();
    GameStateMachine::GetInstance()->Init();
    GameStateMachine::GetInstance()->PushState(GameStateType::STATE_INTRO);

    return 0;
}

void Game::CleanUp()
{
    // Destroy the OpenGL context and window
    if (m_pGLContext)
    {
        SDL_GL_DeleteContext(m_pGLContext);
    }
    if (m_pWindow)
    {
        SDL_DestroyWindow(m_pWindow);
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
    ResourceManager::Destruct();
}

void Game::Run()
{
    // initialize the application
    int error = 0;  
    error |= InitSDL();
    error |= InitOpenGL();
    error |= GameInit();

    // quit if any error occurs
    if (error)
    {
        return;
    }

    while (m_GameRunning)
    {
        HandleEvent(m_event);
        m_currentTime = std::chrono::steady_clock::now();
        m_durationMicro = m_currentTime - m_lastTime;

        // Limit the FPS
        if (m_LimitFPS && m_durationMicro.count() <= 1000000.f / m_LimitFPS)
        {
            continue;
        }

        // calculate time between frame
        m_deltaTime = m_durationMicro.count() / 1000000.f;
        m_lastTime = m_currentTime;

        // update the game
        Update(m_deltaTime);

        // render
        glClear(GL_COLOR_BUFFER_BIT);

        Draw();

        // display on screen
        SDL_GL_SwapWindow(m_pWindow);

        m_GameRunning = GameStateMachine::GetInstance()->IsRunning();
    }

    CleanUp();
}

void Game::HandleEvent(SDL_Event& e)
{
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            // mouse movement
            OnMouseMove(e.motion);
            break;

        case SDL_MOUSEBUTTONDOWN:
            // mouse button pressed
            OnMouseDown(e.button);
            break;

        case SDL_MOUSEBUTTONUP:
            // mouse button released
            OnMouseUp(e.button);
            break;

        case SDL_KEYDOWN:
            // key pressed
            OnKeyDown(e.key);
            break;

        case SDL_KEYUP:
            // key released
            OnKeyUp(e.key);
            break;

        case SDL_QUIT:
            GameStateMachine::GetInstance()->Exit();
            break;

        case SDL_CONTROLLERDEVICEADDED:
            if (SDL_IsGameController(e.cdevice.which))
            {
                SDL_GameController* controller = SDL_GameControllerOpen(e.cdevice.which);
                if (controller)
                {
                    m_controllerArray.push_back(controller);
                }
            }
            OnControllerConnected();
            break;

        case SDL_CONTROLLERDEVICEREMOVED:
        {
            int controllerID = e.cdevice.which;
            // Find the controller
            auto it = std::find_if(m_controllerArray.begin(), m_controllerArray.end(),
                [controllerID](SDL_GameController* controller)
                {
                    return SDL_GameControllerFromInstanceID(controllerID) == controller;
                });
            // Check if controller found
            if (it != m_controllerArray.end())
            {
                // Close the controller before removal
                SDL_GameControllerClose(*it);
                // Remove the controller
                m_controllerArray.erase(it);
            }
            OnControllerDisconnected();
        }
        break; // SDL_CONTROLLERDEVICEREMOVED

        case SDL_CONTROLLERBUTTONDOWN:
            OnControllerButtonDown(e.cbutton);
            break;

        case SDL_CONTROLLERBUTTONUP:
            OnControllerButtonUp(e.cbutton);
            break;

        case SDL_CONTROLLERAXISMOTION:
        {
            switch (e.caxis.axis)
            {
            case SDL_CONTROLLER_AXIS_LEFTX:
                OnControllerLeftJoystickMotionX(e.caxis);
                break;

            case SDL_CONTROLLER_AXIS_LEFTY:
                OnControllerLeftJoystickMotionY(e.caxis);
                break;

            case SDL_CONTROLLER_AXIS_RIGHTX:
                OnControllerRightJoystickMotionX(e.caxis);
                break;

            case SDL_CONTROLLER_AXIS_RIGHTY:
                OnControllerRightJoystickMotionY(e.caxis);
                break;

            case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                OnLeftTriggerMotion(e.caxis);
                break;

            case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                OnRightTriggerMotion(e.caxis);
                break;
            }
        }
        break; // SDL_CONTROLLERAXISMOTION

        default:
            break;
        }
    }
}

void Game::SetWindowTitle(const char* name)
{
    SDL_SetWindowTitle(m_pWindow, name);
}

bool Game::SetVSync(int mode)
{
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        LogError("Failed to set VSync to mode %d, %s", mode, SDL_GetError());
        SDL_ClearError();
    }
    return false;
}

bool Game::SetIgnoreWindowsScaling(bool enabled)
{
#if defined(_WIN64) || defined(_WIN32)
    if (enabled)
    {
        if (SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE))
        {
            LogInfo("Ignored Windows scaling factor");
            return true;
        }
        else
        {
            LogError("Failed to ignore Windows scaling factor");
        }
    }
    else
    {
        // Get the original DPI awareness context
        DPI_AWARENESS_CONTEXT originalContext = GetThreadDpiAwarenessContext();

        // Restore the original DPI awareness context
        if (SetThreadDpiAwarenessContext(originalContext))
        {
            LogInfo("Restored original Windows scaling factor");
            return true;
        }
        else
        {
            LogError("Failed to restore original Windows scaling factor");
            return false;
        }
    }
#else
    // Not on Windows platform, no action needed
    LogWarning("Not Windows platform");
    return false;
#endif // _WIN64 || _WIN32

    return false;
}

void Game::SetWindowResolution(int width, int height)
{
    SDL_SetWindowSize(m_pWindow, width, height);
    SetDefaultViewport();
}

void Game::SetWindowBorderless()
{
    SDL_SetWindowBordered(m_pWindow, SDL_FALSE);
}

void Game::SetWindowWindowed()
{
    int error = SDL_SetWindowFullscreen(m_pWindow, 0);
    if (error)
    {
        LogError("Set fullscreen failed, %s", SDL_GetError());
        SDL_ClearError();
    }
    SetDefaultViewport();
}

int Game::SetFullScreen()
{
    int error = SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
    if (error)
    {
        LogError("Set fullscreen failed, %s", SDL_GetError());
        SDL_ClearError();
        return -1;
    }
    SetDefaultViewport();
    return 0;
}

int Game::SetFullScreenBorderless()
{
    int error = SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (error)
    {
        LogError("Set fullscreen borderless failed, %s", SDL_GetError());
        SDL_ClearError();
        return -1;
    }
    SetDefaultViewport();
    return 0;
}

void Game::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Game::SetFPSLimit(float FPS)
{
    float m_LimitFPS = FPS;
}

int Game::GetWindowWidth() const
{
    return m_ScreenWidth;
}

int Game::GetWindowHeight() const
{
    return m_ScreenHeight;
}

void Game::Draw()
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->Draw();
    }
}

void Game::Update(float deltaTime)
{
    // update state change
    GameStateMachine::GetInstance()->Update();
    // get current game state and update
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->Update(deltaTime);
    }
}

void Game::OnKeyDown(const SDL_KeyboardEvent& keyevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnKeyDown(keyevent);
    }
}

void Game::OnKeyUp(const SDL_KeyboardEvent& keyevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnKeyUp(keyevent);
    }
}

void Game::OnMouseDown(const SDL_MouseButtonEvent& mouseevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseDown(mouseevent);
    }
}

void Game::OnMouseUp(const SDL_MouseButtonEvent& mouseevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseUp(mouseevent);
    }
}

void Game::OnMouseMove(const SDL_MouseMotionEvent& motionevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseMove(motionevent);
    }
}

void Game::OnMouseScroll(const SDL_MouseWheelEvent& wheelevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnMouseScroll(wheelevent);
    }
}

void Game::OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerButtonDown(buttonevent);
    }
}

void Game::OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonevent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerButtonUp(buttonevent);
    }
}

void Game::OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerLeftJoystickMotionX(joystickEvent);
    }
}

void Game::OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerLeftJoystickMotionY(joystickEvent);
    }
}

void Game::OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerRightJoystickMotionX(joystickEvent);
    }
}

void Game::OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerRightJoystickMotionY(joystickEvent);
    }
}

void Game::OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnLeftTriggerMotion(triggerEvent);
    }
}

void Game::OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnRightTriggerMotion(triggerEvent);
    }
}

void Game::OnControllerConnected()
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerConnected();
    }
}

void Game::OnControllerDisconnected()
{
    if (GameStateMachine::GetInstance()->HasState())
    {
        GameStateMachine::GetInstance()->GetCurrentState()->OnControllerDisconnected();
    }
}

void Game::SetDefaultViewport()
{
    SDL_GetWindowSize(m_pWindow, &m_ScreenWidth, &m_ScreenHeight);
    glViewport(0, 0, m_ScreenWidth, m_ScreenHeight);
}

void Game::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}
