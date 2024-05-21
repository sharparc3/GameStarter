#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <chrono>
#include <vector>
#include "Global.h"
#include "SingletonDclp.h"

class Game final : public SingletonDclp<Game>
{
public:
	int InitSDL();
	int InitOpenGL();
	int GameInit();
	void CleanUp();
	void Run();
	void HandleEvent(SDL_Event& e);

	// Utilities
	void SetWindowTitle(const char* name);
	bool SetVSync(int mode);
	bool SetIgnoreWindowsScaling(bool enabled = true);
	void SetWindowResolution(int width, int height);
	void SetWindowBorderless();
	void SetWindowWindowed();
	int SetFullScreen();
	int SetFullScreenBorderless();
	void SetClearColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void SetFPSLimit(float FPS);
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	void SetDefaultViewport();
	void SetViewport(int x, int y, int width, int height);

private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_pGLContext;
	SDL_Event m_event;
	std::vector<SDL_GameController*> m_controllerArray;
	std::chrono::steady_clock::time_point m_lastTime, m_currentTime;
	std::chrono::duration<float, std::micro> m_durationMicro;
	float m_deltaTime;
	float m_LimitFPS;
	int m_ScreenHeight, m_ScreenWidth;
	bool m_GameRunning;

private:
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
};