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

static int GetInt(int from, int to) {
    // Initialize random number engine with a non-deterministic seed 
    static std::random_device rd;
    static std::mt19937 generator(rd());

    // Define the distribution
    std::uniform_int_distribution<> distribution(from, to);

    // Generate a random number within the range
    return distribution(generator);
}

GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
    std::cout << "Switched to intro state.\n";

    // load resources
    ResourceManager::GetInstance()->LoadMesh("quad.nfg");
    ResourceManager::GetInstance()->LoadMesh("quad_center.nfg");
    ResourceManager::GetInstance()->LoadShader("quad");
    ResourceManager::GetInstance()->LoadTexture("compiling.png");

    // get resources
    //auto mesh = ResourceManager::GetInstance()->GetMesh("quad.nfg");
    //auto mesh_center = ResourceManager::GetInstance()->GetMesh("quad.nfg");
    auto shader = ResourceManager::GetInstance()->GetShader("quad");
    auto texture = ResourceManager::GetInstance()->GetTexture("compiling.png");
    
    // set up camera
    m_camera = std::make_shared<Camera>();
    auto game = Game::GetInstance();
    int sWidth = game->GetWindowWidth();
    int sHeight = game->GetWindowHeight();
    m_camera->SetOrthographicProjection(0.f, (float)sWidth, 0.f, (float)sHeight);

    // set up renderer
    m_renderer = std::make_shared<Renderer>(m_camera, shader);

    // create a sprite 
    m_sprite = std::make_shared<Sprite2D>(texture);

    // set up sprite
    m_sprite->SetPosition(400.f, 400.f);
    m_sprite->SetRotation(45.0f);
    m_sprite->SetSize(413.0f, 360.0f);

    // add to renderer 
    m_renderer->AddObject(m_sprite);

    m_sprite2 = std::make_shared<Sprite2D>(texture);
    m_sprite2->SetPosition(480.f, 270.f, 0.f);
    m_sprite2->SetRotation(0.0f);
    m_sprite2->SetSize(206.f, 180.f);

    auto sprite3 = std::make_shared<Sprite2D>(texture);
    sprite3->SetPosition(400.f, 400.f);
    sprite3->SetRotation(0.f);
    sprite3->SetSize(413.0f, 360.0f);
    m_renderer->AddObject(sprite3);

    //m_renderer->AddObject(m_sprite2);

    for (int i = 3; i < 3000; i++)
    {
        auto sprite = std::make_shared<Sprite2D>(texture);
        sprite->SetPosition((float)-500.f, 0.f);
        sprite->SetRotation(0.0f);
        sprite->SetSize(412.f, 360.f);
        m_renderer->AddObject(sprite);
    }

    joyLeftX = joyLeftY = joyRightX = joyRightY = 0;
}

void GSIntro::Update(float deltaTime)
{
    auto game = Game::GetInstance();
    int sWidth = game->GetWindowWidth();
    int sHeight = game->GetWindowHeight();
    m_camera->SetOrthographicProjection(0.f, (float)sWidth, 0.f, (float)sHeight);
}

void GSIntro::Draw()
{
    m_renderer->Render();
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
    case SDLK_t:
        // test resize windows
        gameIns->SetWindowResolution(1600, 900);
        m_camera->SetOrthographicProjection(0.f, (float)gameIns->GetWindowWidth(), 0.f, (float)gameIns->GetWindowHeight());
        break;
    case SDLK_f:
        gameIns->SetFullScreen();
        m_camera->SetOrthographicProjection(0.f, (float)gameIns->GetWindowWidth(), 0.f, (float)gameIns->GetWindowHeight());
        break;
    case SDLK_g:
        gameIns->SetFullScreenBorderless();
        m_camera->SetOrthographicProjection(0.f, (float)gameIns->GetWindowWidth(), 0.f, (float)gameIns->GetWindowHeight());
        break;
    case SDLK_1:
        gameIns->SetWindowResolution(1920, 1080);
        m_camera->SetOrthographicProjection(0.f, (float)gameIns->GetWindowWidth(), 0.f, (float)gameIns->GetWindowHeight());
        break;
    case SDLK_2:
        gameIns->SetWindowResolution(2560, 1440);
        m_camera->SetOrthographicProjection(0.f, (float)gameIns->GetWindowWidth(), 0.f, (float)gameIns->GetWindowHeight());
        break;
    case SDLK_ESCAPE:
        gameIns->SetWindowWindowed();
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
        GameStateMachine::GetInstance()->PushState(GameStateType::STATE_MENU);
        break;
    case SDL_BUTTON_RIGHT:
        std::cout << "State popped: Intro.\n";
        GameStateMachine::GetInstance()->PopState();
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
    //std::cout << "Left joystick: " << directionVec.x << ", " << directionVec.y << "\n";
    std::cout << "Left joystick: " << joyLeftX << ", " << joyLeftY << "\n";
}

void GSIntro::OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    joyLeftY = joystickEvent.value;
    glm::vec2 directionVec(joyLeftX, joyLeftY);
    directionVec = glm::normalize(directionVec);
    //std::cout << "Left joystick: " << directionVec.x << ", " << directionVec.y << "\n";
    std::cout << "Left joystick: " << joyLeftX << ", " << joyLeftY << "\n";
}

void GSIntro::OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent)
{
    joyRightX = joystickEvent.value;
    glm::vec2 directionVec(joyRightX, joyRightY);
    directionVec = glm::normalize(directionVec);
    //std::cout << "Right joystick: " << directionVec.x << ", " << directionVec.y << "\n";
    std::cout << "Right joystick: " << joyRightX << ", " << joyRightY << "\n";
}

void GSIntro::OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent)
{
    joyRightY = joystickEvent.value;
    glm::vec2 directionVec(joyRightX, joyRightY);
    directionVec = glm::normalize(directionVec);
    //std::cout << "Right joystick: " << directionVec.x << ", " << directionVec.y << "\n";
    std::cout << "Right joystick: " << joyRightX << ", " << joyRightY << "\n";
}

void GSIntro::OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonEvent)
{
    switch (buttonEvent.button)
    {
    case SDL_CONTROLLER_BUTTON_A:
        // Handle A button press
        std::cout << "A button down\n";
        break;
    case SDL_CONTROLLER_BUTTON_B:
        // Handle B button press
        std::cout << "B button down\n";
        break;
    case SDL_CONTROLLER_BUTTON_X:
        // Handle X button press
        std::cout << "X button down\n";
        break;
    case SDL_CONTROLLER_BUTTON_Y:
        // Handle Y button press
        std::cout << "Y button down\n";
        break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        // Handle left bumper press
        std::cout << "LB down\n";
        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        // Handle right bumper press
        std::cout << "RB down\n";
        break;
    case SDL_CONTROLLER_BUTTON_BACK:
        // Handle back button press
        std::cout << "BACK button down\n";
        break;
    case SDL_CONTROLLER_BUTTON_START:
        // Handle start button press
        std::cout << "START button down\n";
        break;
    case SDL_CONTROLLER_BUTTON_GUIDE:
        // Handle guide button press
        std::cout << "GUIDE button down\n";
        break;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        // Handle left stick click
        std::cout << "LSB down\n";
        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        // Handle right stick click
        std::cout << "RSB down\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        // Handle D-pad up press
        std::cout << "DPAD-UP down\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        // Handle D-pad down press
        std::cout << "DPAD-DOWN down\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        // Handle D-pad left press
        std::cout << "DPAD-LEFT down\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        // Handle D-pad right press
        std::cout << "DPAD-RIGHT down\n";
        break;

    default:
        // Handle other button presses or unknown buttons
        break;
    }

}

void GSIntro::OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonEvent)
{
    switch (buttonEvent.button)
    {
    case SDL_CONTROLLER_BUTTON_A:
        // Handle A button up
        std::cout << "A up\n";
        break;
    case SDL_CONTROLLER_BUTTON_B:
        // Handle B button up
        std::cout << "B up\n";
        break;
    case SDL_CONTROLLER_BUTTON_X:
        // Handle X button up
        std::cout << "X up\n";
        break;
    case SDL_CONTROLLER_BUTTON_Y:
        // Handle Y button up
        std::cout << "Y up\n";
        break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        // Handle left bumper up
        std::cout << "LB up\n";
        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        // Handle right bumper up
        std::cout << "RB up\n";
        break;
    case SDL_CONTROLLER_BUTTON_BACK:
        // Handle back button up
        std::cout << "BACK up\n";
        break;
    case SDL_CONTROLLER_BUTTON_START:
        // Handle start button up
        std::cout << "START up\n";
        break;
    case SDL_CONTROLLER_BUTTON_GUIDE:
        // Handle guide button up
        std::cout << "GUIDE up\n";
        break;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
        // Handle left stick up
        std::cout << "LSB up\n";
        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
        // Handle right stick up
        std::cout << "RSB up\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        // Handle D-pad up up
        std::cout << "DPAD-UP up\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        // Handle D-pad down up
        std::cout << "DPAD-DOWN up\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        // Handle D-pad left up
        std::cout << "DPAD-LEFT up\n";
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        // Handle D-pad right up
        std::cout << "DPAD-RIGHT up\n";
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
    std::cout << "LT: " << normalized << "\n";
}

void GSIntro::OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent)
{
    short value = triggerEvent.value;
    float normalized = value >= 0 ? (float)value / 32767 : (float)value / 32768;
    std::cout << "RT: " << normalized << "\n";
}

void GSIntro::ImGuiDraw()
{
    auto& io = ImGui::GetIO();
    {
        static bool a, b;
        static float f = 0.0f;
        static int counter = 0;
        static char textfield[64] = "";

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &a);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &b);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::InputText("Enter text here", textfield, IM_ARRAYSIZE(textfield));

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
}
