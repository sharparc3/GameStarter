#include "GSMenu.h"
#include "ResourceManager.h"
#include "SpriteAnimation.h"
#include "Renderer.h"
#include "Camera.h"
#include "GameStateMachine.h"

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

	auto mesh = ResourceManager::GetInstance()->GetMesh("sprite2d.nfg");
	auto shader = ResourceManager::GetInstance()->GetShader("animation");
	auto texture = ResourceManager::GetInstance()->GetTexture("cat_anim.png");
	texture->SetFilter(1);

	m_animation = std::make_shared<SpriteAnimation>(2, mesh, texture, 0.1f, 6);
	m_camera = std::make_shared<Camera>();
	m_camera->SetOrthographicProjection();

	m_renderer = std::make_shared<Renderer>(m_camera, shader);

	m_animation->SetPosition(0.f, 0.f, 0.f);
	m_animation->SetRotation(0.f, 0.f);
	m_animation->SetScale(250.f, 200.f);

	m_renderer->AddObject(m_animation);
}

void GSMenu::Update(float deltaTime)
{
	m_animation->Update(deltaTime);
}

void GSMenu::Draw()
{
	//// Specify vertex positions (2D coordinates)
	//GLfloat vertices[] = {
	//	-0.5f,  0.5f,  // Top-left vertex
	//	 0.5f,  0.5f,  // Top-right vertex
	//	 0.5f, -0.5f,  // Bottom-right vertex
	//	-0.5f, -0.5f   // Bottom-left vertex
	//};

	//// Set the color to green
	//glColor3f(0.0f, 1.0f, 0.0f);

	//// Begin drawing a primitive
	//glBegin(GL_QUADS); // Indicate we want to draw a quad (rectangle)

	//// Specify vertices for the rectangle 
	//glVertex2f(vertices[0], vertices[1]);
	//glVertex2f(vertices[2], vertices[3]);
	//glVertex2f(vertices[4], vertices[5]);
	//glVertex2f(vertices[6], vertices[7]);

	//// Finish drawing
	//glEnd();
	m_renderer->Render();
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

