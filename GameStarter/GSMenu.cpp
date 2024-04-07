#include "GSMenu.h"
#include "ResourceManager.h"
#include "SpriteAnimation.h"
#include "Renderer.h"
#include "Camera.h"
#include "GameStateMachine.h"
#include "BatchRenderer.h"
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


GSMenu::GSMenu()
{
}

GSMenu::~GSMenu()
{
	m_renderer = nullptr;
	m_camera = nullptr;
}

void GSMenu::Init()
{
	std::cout << "Switched to menu state.\n";
	ResourceManager::GetInstance()->LoadShader("animation");
	ResourceManager::GetInstance()->LoadTexture("cat_anim.png");
	ResourceManager::GetInstance()->LoadShader("sprite2d_batch");

	auto mesh = ResourceManager::GetInstance()->GetMesh("sprite2d.nfg");
	auto shader = ResourceManager::GetInstance()->GetShader("animation");
	auto texture = ResourceManager::GetInstance()->GetTexture("cat_anim.png");
	texture->SetFilter(1);
	auto batchshader = ResourceManager::GetInstance()->GetShader("sprite2d_batch");
	auto texture2 = ResourceManager::GetInstance()->GetTexture("compiling.png");
	m_animation = std::make_shared<SpriteAnimation>(2, mesh, texture, 0.1f, 6);
	m_camera = std::make_shared<Camera>();
	m_camera->SetOrthographicProjection();

	m_renderer = std::make_shared<Renderer>(m_camera, shader);

	m_animation->SetPosition(0.f, 0.f, 0.f);
	m_animation->SetRotation(0.f, 0.f);
	m_animation->SetScale(250.f, 200.f);

	m_renderer->AddObject(m_animation);

	m_batchRenderer = std::make_shared<BatchRenderer>(20000, m_camera, batchshader);
	for (int i = 0; i < 2000; i++)
	{
		auto sprite = std::make_shared<Sprite2D>(i, mesh, texture2);
		sprite->SetPosition((float)GetInt(0, 960), (float)GetInt(0, 540), 0.f);
		sprite->SetRotation(0.0f);
		sprite->SetScale(412.f, 360.f);
		m_batchRenderer->AddObject(sprite);
	}
}

void GSMenu::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
}

void GSMenu::Draw()
{
	m_renderer->Render();
	m_batchRenderer->Render();
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

