#include "GSIntro.h"
#include "Renderer.h"
#include "Camera.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "Sprite2D.h"

#include <random>
#include <chrono>

static int GetInt(int from, int to) {
    // Initialize random number engine with a non-deterministic seed 
    static std::random_device rd;
    static std::mt19937 generator(rd());

    // Define the distribution
    std::uniform_int_distribution<> distribution(from, to);

    // Generate a random number within the range
    return distribution(generator);
}

GSIntro::GSIntro()
{
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
    auto mesh = ResourceManager::GetInstance()->GetMesh("quad.nfg");
    auto mesh_center = ResourceManager::GetInstance()->GetMesh("quad.nfg");
    auto shader = ResourceManager::GetInstance()->GetShader("quad");
    auto texture = ResourceManager::GetInstance()->GetTexture("compiling.png");
    
    // set up camera
    m_camera = std::make_shared<Camera>();
    m_camera->SetOrthographicProjection();

    // set up renderer
    m_renderer = std::make_shared<Renderer>(m_camera, shader);

    // create a sprite 
    m_sprite = std::make_shared<Sprite2D>(0, mesh, texture);

    // set up sprite
    m_sprite->SetPosition(0.f, 0.f, 0.0f);
    m_sprite->SetRotation(0.0f);
    m_sprite->SetScale(413.0f, 360.0f);

    // add to renderer 
    m_renderer->AddObject(m_sprite);

    m_sprite2 = std::make_shared<Sprite2D>(1, mesh, texture);
    m_sprite2->SetPosition(480.f, 270.f, 0.f);
    m_sprite2->SetRotation(0.0f);
    m_sprite2->SetScale(206.f, 180.f);

    m_renderer->AddObject(m_sprite2);

    for (int i = 2; i < 1500; i++)
    {
        auto sprite = std::make_shared<Sprite2D>(i, mesh_center, texture);
        sprite->SetPosition((float)GetInt(0, 960), (float)GetInt(0, 540), 0.f);
        sprite->SetRotation(0.0f);
        sprite->SetScale(412.f, 360.f);
        m_renderer->AddObject(sprite);
    }
}

void GSIntro::Update(float deltaTime)
{

}

void GSIntro::Draw()
{
    //m_renderer->Render();
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
