#include "GSMenu.h"
#include "ResourceManager.h"
#include "SpriteAnimation.h"
#include "Renderer.h"
#include "Camera.h"
#include "GameStateMachine.h"
#include "BatchRenderer.h"
#include "Sprite2D.h"
#include "Sound.h"
#include "SoundPlayer.h"
#include "Text.h"

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
	m_animationRenderer = nullptr;
	m_camera = nullptr;
}

void GSMenu::Init()
{
	std::cout << "Switched to menu state.\n";

	ResourceManager::GetInstance()->LoadShader("animation");
	ResourceManager::GetInstance()->LoadTexture("cat_anim.png");
	ResourceManager::GetInstance()->LoadShader("quad_batch");
	ResourceManager::GetInstance()->LoadSound("mouse_down.wav");
	ResourceManager::GetInstance()->LoadSound("mouse_up.wav");
	ResourceManager::GetInstance()->LoadSound("click.mp3");
	ResourceManager::GetInstance()->LoadShader("quad");
	//ResourceManager::GetInstance()->LoadMesh("quad_center.nfg");

	auto mesh = ResourceManager::GetInstance()->GetMesh("quad.nfg");
	auto mesh_center = ResourceManager::GetInstance()->GetMesh("quad_center.nfg");
	auto shader_anm = ResourceManager::GetInstance()->GetShader("animation");
	auto shader_sprite = ResourceManager::GetInstance()->GetShader("quad");
	auto texture = ResourceManager::GetInstance()->GetTexture("cat_anim.png");

	texture->SetFilter(1);
	auto batchshader = ResourceManager::GetInstance()->GetShader("quad_batch");
	auto texture2 = ResourceManager::GetInstance()->GetTexture("compiling.png");
	m_animation = std::make_shared<SpriteAnimation>(2, mesh, texture, 0.1f, 6);
	m_camera = std::make_shared<Camera>();
	m_camera->SetOrthographicProjection();

	m_animationRenderer = std::make_shared<Renderer>(m_camera, shader_anm);
	m_spriteRenderer = std::make_shared<Renderer>(m_camera, shader_sprite);

	m_animation->SetPosition(0.f, 0.f, 0.f);
	m_animation->SetRotation(0.f, 0.f);
	m_animation->SetScale(250.f, 200.f);

	m_animationRenderer->AddObject(m_animation);

	m_batchRenderer = std::make_shared<BatchRenderer>(20000, m_camera, batchshader);
	for (int i = 0; i < 1500; i++)
	{
		auto sprite = std::make_shared<Sprite2D>(i, mesh_center, texture2);
		sprite->SetPosition((float)GetInt(0, 960), (float)GetInt(0, 540), 0.f);
		sprite->SetRotation(0.0f);
		sprite->SetScale(412.f, 360.f);
		m_batchRenderer->AddObject(sprite);
	}

	m_soundMouseDown = ResourceManager::GetInstance()->GetSound("mouse_down.wav");
	m_soundMouseUp = ResourceManager::GetInstance()->GetSound("mouse_up.wav");
	m_firstMouseDown = false;

	//ResourceManager::GetInstance()->LoadFont("Roboto-Regular.ttf");
	//auto font = ResourceManager::GetInstance()->GetFont("Roboto-Regular.ttf");
	SDL_Color textColor = { 255, 0, 0, 255 };
	m_textObj = std::make_shared<Text>(0, "Hello\nThis text is rendered as a 2D sprite", "Roboto-Regular.ttf", 48, textColor);
	m_textObj->SetPosition(100.f, 100.f);
	m_spriteRenderer->AddObject(m_textObj);
}

void GSMenu::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
	m_textObj->UpdateText();
}

void GSMenu::Draw()
{
	//m_batchRenderer->Render();
	//m_animationRenderer->Render();
	m_spriteRenderer->Render();
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
	if (!m_firstMouseDown)
	{
		m_firstMouseDown = true;
		SoundPlayer::GetInstance()->Play(m_soundMouseDown);
	}
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
	SoundPlayer::GetInstance()->Play(m_soundMouseUp);
	m_firstMouseDown = false;
}

void GSMenu::OnMouseMove(const SDL_MouseMotionEvent& motionevent)
{
}

void GSMenu::OnMouseScroll(const SDL_MouseWheelEvent& wheelevent)
{
}
