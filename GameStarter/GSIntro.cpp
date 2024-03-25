#include "GSIntro.h"

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
    ResourceManager::GetInstance()->LoadMesh("sprite2d.nfg");
    ResourceManager::GetInstance()->LoadShader("sprite2d");
    ResourceManager::GetInstance()->LoadTexture("compiling.png");

    // get resources
    auto mesh = ResourceManager::GetInstance()->GetMesh("sprite2d.nfg");
    auto shader = ResourceManager::GetInstance()->GetShader("sprite2d");
    auto texture = ResourceManager::GetInstance()->GetTexture("compiling.png");
    
    // set up camera
    m_camera = Camera();
    m_camera.SetOrthographicProjection();
    //m_camera.SetPosition(glm::vec3(0.f, 0.f, 0.f));
    //m_camera.SetTarget(glm::vec3(0.f, 0.f, -1.f));
    //m_camera.SetUpVector(glm::vec3(0.f, 1.f, 0.f));

    // set up renderer
    m_renderer.SetCamera(std::make_shared<Camera>(m_camera));

    // create a sprite 
    m_sprite = std::make_shared<Sprite2D>(0, mesh, shader, texture);

    // set up sprite
    m_sprite->SetPosition(0.f, 0.f, 0.0f);
    m_sprite->SetRotation(0.0f);
    //m_sprite->SetScale(413.0f * 2, 360.0f * 2);
    m_sprite->SetScale(400.f, 400.f);

    // add to renderer 
    m_renderer.AddObject(m_sprite);
}

void GSIntro::Update(float deltaTime)
{

}

void GSIntro::Draw()
{
    m_renderer.Render();
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
