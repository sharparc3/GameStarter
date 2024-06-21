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
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>


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

    // for imgui
    if (SDL_Init(SDL_INIT_TIMER))
    {
        LogError("SDL timer initialization failed, %s", SDL_GetError());
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
    m_GLContext = SDL_GL_CreateContext(m_pWindow);

    if (!m_GLContext)
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
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        return -1;
    }

    SDL_GL_MakeCurrent(m_pWindow, m_GLContext);

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

    // default FPS limit is screen refresh rate
    m_LimitFPS = 0.f;

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
    GSM()->PushState(GameStateType::STATE_INTRO);

    RESOURCE()->LoadMesh("quad.nfg");
    RESOURCE()->LoadMesh("quad_center.nfg");


    return 0;
}

void Game::CleanUp()
{
    // Destroy the OpenGL context and window
    if (m_GLContext)
    {
        SDL_GL_DeleteContext(m_GLContext);
    }
    if (m_pWindow)
    {
        SDL_DestroyWindow(m_pWindow);
    }

    // free singleton classes
    while (GSM()->HasState())
    {

    }
    GSM()->CleanUp();
    GameStateMachine::Destruct();
    RESOURCE()->FreeAllResources();
    ResourceManager::Destruct();
    SOUNDPLAYER()->Deinit();
    SoundPlayer::Destruct();

    // ImGUI quit
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Quit SDL
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::Run()
{
    // initialize the application
    int error = 0;  
    error |= InitSDL();
    error |= InitOpenGL();
    error |= GameInit();
    error |= InitImGUI();

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

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // state ImGui draw
        if (GSM()->HasState())
        {
            GSM()->GetCurrentState()->ImGuiDraw();
        }

        // update the game
        Update(m_deltaTime);

        // render
        glClear(GL_COLOR_BUFFER_BIT);

        // game draw
        Draw();

        // ImGui render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // display on screen
        SDL_GL_SwapWindow(m_pWindow);

        m_GameRunning = GSM()->IsRunning();
    }

    CleanUp();
}

void Game::HandleEvent(SDL_Event& e)
{
    while (SDL_PollEvent(&e))
    {
        ImGui_ImplSDL2_ProcessEvent(&e);
        
        ImGuiIO& io = ImGui::GetIO();

        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            // event is consumed by ImGui so skip it
            if (io.WantCaptureMouse)
            {
                break;
            }
            // mouse movement
            OnMouseMove(e.motion);
            break;

        case SDL_MOUSEBUTTONDOWN:
            // event is consumed by ImGui so skip it
            if (io.WantCaptureMouse)
            {
                break;
            }
            // mouse button pressed
            OnMouseDown(e.button);
            break;

        case SDL_MOUSEBUTTONUP:
            // event is consumed by ImGui so skip it
            if (io.WantCaptureMouse)
            {
                break;
            }
            // mouse button released
            OnMouseUp(e.button);
            break;

        case SDL_MOUSEWHEEL:
            // event is consumed by ImGui so skip it
            if (io.WantCaptureMouse)
            {
                break;
            }
            OnMouseScroll(e.wheel);
            break;

        case SDL_KEYDOWN:
            // event is consumed by ImGui so skip it
            if (io.WantCaptureKeyboard)
            {
                break;
            }
            // key pressed
            OnKeyDown(e.key);
            break;

        case SDL_KEYUP:
            // event is consumed by ImGui so skip it
            if (io.WantCaptureKeyboard)
            {
                break;
            }
            // key released
            OnKeyUp(e.key);
            break;

        case SDL_QUIT:
            GSM()->Exit();
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
    if (SDL_GL_SetSwapInterval(mode) < 0)
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
    m_LimitFPS = FPS;
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
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->Draw();
    }
}

void Game::Update(float deltaTime)
{
    // update state change
    GSM()->Update();
    // get current game state and update
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->Update(deltaTime);
    }
}

void Game::OnKeyDown(const SDL_KeyboardEvent& keyevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnKeyDown(keyevent);
    }
}

void Game::OnKeyUp(const SDL_KeyboardEvent& keyevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnKeyUp(keyevent);
    }
}

void Game::OnMouseDown(const SDL_MouseButtonEvent& mouseevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnMouseDown(mouseevent);
    }
}

int Game::InitImGUI()
{
    // needed for ImGUI to work
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    bool success = true;
    const char* glsl_version = "#version 130";
    success &= ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_GLContext);
    success &= ImGui_ImplOpenGL3_Init(glsl_version);

    if (success)
    {
        return 0;
    }
    return 1;
}

void Game::OnMouseUp(const SDL_MouseButtonEvent& mouseevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnMouseUp(mouseevent);
    }
}

void Game::OnMouseMove(const SDL_MouseMotionEvent& motionevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnMouseMove(motionevent);
    }
}

void Game::OnMouseScroll(const SDL_MouseWheelEvent& wheelevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnMouseScroll(wheelevent);
    }
}

void Game::OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerButtonDown(buttonevent);
    }
}

void Game::OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonevent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerButtonUp(buttonevent);
    }
}

void Game::OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerLeftJoystickMotionX(joystickEvent);
    }
}

void Game::OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerLeftJoystickMotionY(joystickEvent);
    }
}

void Game::OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerRightJoystickMotionX(joystickEvent);
    }
}

void Game::OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerRightJoystickMotionY(joystickEvent);
    }
}

void Game::OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnLeftTriggerMotion(triggerEvent);
    }
}

void Game::OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnRightTriggerMotion(triggerEvent);
    }
}

void Game::OnControllerConnected()
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerConnected();
    }
}

void Game::OnControllerDisconnected()
{
    if (GSM()->HasState())
    {
        GSM()->GetCurrentState()->OnControllerDisconnected();
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
