#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <chrono>
#include <vector>
#include <glm/glm.hpp>
#include "Config.h"
#include "SingletonDclp.h"


/**
 * @brief Encapsulates the main game functionality and attributes.
 *
 * The Game class manages the main game loop, rendering, input handling,
 * and other core functionalities.
 */
class Game final : public SingletonDclp<Game>
{
public:
	void CleanUp();
	void Run();

	/**
	 * @brief Sets the title of the window.
	 * @param name The title to set for the window.
	 */
	void SetWindowTitle(const char* name);

	/**
	 * @brief Sets the vertical synchronization (VSync) mode.
	 * @param mode The mode to set (0 for off, 1 for on, -1 for adaptive vsync).
	 * @return true if successful, false otherwise.
	 */
	bool SetVSync(int mode);

	/**
	 * @brief Sets whether to ignore Windows scaling for DPI.
	 * @param enabled Whether to enable (true) or disable (false) ignoring Windows scaling.
	 * @return true if successful, false otherwise.
	 */
	bool SetIgnoreWindowsScaling(bool enabled = true);

	/**
	 * @brief Sets the resolution of the window.
	 * @param width The width of the window.
	 * @param height The height of the window.
	 */
	void SetWindowResolution(int width, int height);

	/**
	 * @brief Sets the window to borderless mode.
	 */
	void SetWindowBorderless();

	/**
	 * @brief Sets the window to windowed mode.
	 */
	void SetWindowWindowed();

	/**
	 * @brief Sets the window to full-screen mode.
	 * @return 0 if successful, -1 if an error occurs.
	 */
	int SetFullScreen();

	/**
	 * @brief Sets the window to full-screen borderless mode.
	 * @return 0 if successful, -1 if an error occurs.
	 */
	int SetFullScreenBorderless();

	/**
	 * @brief Sets the clear color for the screen.
	 * @param r Red component of the color (default is 1.0).
	 * @param g Green component of the color (default is 1.0).
	 * @param b Blue component of the color (default is 1.0).
	 * @param a Alpha (transparency) component of the color (default is 1.0).
	 */
	void SetClearColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

	/**
	 * @brief Sets the frame rate limit (FPS) for rendering.
	 * @param FPS The desired FPS limit (0 is unlimited).
	 */
	void SetFPSLimit(float FPS);

	/**
	 * @brief Gets the width of the window.
	 * @return The width of the window in pixel.
	 */
	int GetWindowWidth() const;

	/**
	 * @brief Gets the height of the window.
	 * @return The height of the window in pixel.
	 */
	int GetWindowHeight() const;

	/**
	 * @brief Sets the default viewport for rendering (match the window size).
	 */
	void SetDefaultViewport();

	/**
	 * @brief Sets a custom viewport for rendering.
	 * @param x X-coordinate of the viewport.
	 * @param y Y-coordinate of the viewport.
	 * @param width Width of the viewport.
	 * @param height Height of the viewport.
	 */
	void SetViewport(int x, int y, int width, int height);

private:
	/**
	 * @brief Pointer to the window created by SDL.
	 *
	 * This pointer represents the main window of the game where rendering occurs.
	 */
	SDL_Window* m_pWindow;

	/**
	 * @brief OpenGL context for rendering.
	 *
	 * This context is used for managing all OpenGL state and operations
	 * associated with the SDL window.
	 */
	SDL_GLContext m_GLContext;

	/**
	 * @brief Event handler for SDL events.
	 *
	 * This structure holds events such as keyboard, mouse, and controller inputs
	 * that are processed during the game loop.
	 */
	SDL_Event m_event;

	/**
	 * @brief Array of game controllers.
	 *
	 * This vector stores pointers to connected game controllers, allowing the
	 * game to handle multiple controllers simultaneously (in the future).
	 */
	std::vector<SDL_GameController*> m_controllerArray;

	/**
	 * @brief Timestamp of the last update.
	 *
	 * This timestamp records the time of the last frame update, used for calculating
	 * the elapsed time between frames.
	 */
	std::chrono::steady_clock::time_point m_lastTime;

	/**
	 * @brief Timestamp of the current update.
	 *
	 * This timestamp records the current time at the start of each frame update,
	 * used for calculating the elapsed time since the last update.
	 */
	std::chrono::steady_clock::time_point m_currentTime;

	/**
	 * @brief Duration in microseconds between frames.
	 *
	 * This duration represents the elapsed time between the last and current frame
	 * updates, measured in microseconds.
	 */
	std::chrono::duration<float, std::micro> m_durationMicro;

	/**
	 * @brief Delta time between frames.
	 *
	 * This float value represents the time elapsed between the last and current frame
	 * updates, used for time-based calculations within the game loop.
	 */
	float m_deltaTime;

	/**
	 * @brief Frame rate limit.
	 *
	 * This float value sets the maximum frames per second (FPS) limit for the game,
	 * controlling the rendering speed and ensuring a consistent frame rate.
	 */
	float m_LimitFPS;

	/**
	 * @brief Screen height in pixels.
	 *
	 * This integer value represents the height of the game window in pixels.
	 */
	int m_ScreenHeight;

	/**
	 * @brief Screen width in pixels.
	 *
	 * This integer value represents the width of the game window in pixels.
	 */
	int m_ScreenWidth;

	/**
	 * @brief Flag indicating if the game is running.
	 *
	 * This boolean flag controls the main game loop. If set to true, the game is running;
	 * if set to false, the game loop will exit, and the game will terminate.
	 */
	bool m_GameRunning;

private:
	/**
	 * @brief Initializes SDL (Simple DirectMedia Layer).
	 * @return 0 if successful, -1 if initialization fails.
	 */
	int InitSDL();

	/**
	 * @brief Initializes OpenGL for rendering.
	 * @return 0 if successful, -1 if initialization fails.
	 */
	int InitOpenGL();

	/**
	 * @brief Initializes  Dear ImGui for user interface.
	 * @return 0 if successful, -1 if initialization fails.
	 */
	int InitImGUI();

	/**
	 * @brief Initializes game-specific resources and subsystems.
	 * @return 0 if successful, -1 if initialization fails.
	 */
	int GameInit();

	/**
	 * @brief Handles SDL events.
	 * @param e Reference to the SDL event to handle.
	 * @link SDL_Event SDL_Event union documentation
	 *      @url https://wiki.libsdl.org/SDL2/SDL_Event
	 *      @endlink
	 */
	void HandleEvent(SDL_Event& e);


	/**
	 * @brief Draws the game scene.
	 */
	void Draw();

	/**
	 * @brief Updates the game state based on elapsed time.
	 * @param deltaTime Time elapsed since the last update.
	 */
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