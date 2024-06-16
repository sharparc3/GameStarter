#pragma once
#include <SDL2/SDL_events.h>
#include "Config.h"

enum class GameStateType
{
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY,
	STATE_COUNT
};

/**
 * @brief Abstract base class for defining game states in a game application.
 *
 * This class serves as the base for all game states within the application.
 * Each derived class represents a specific state in the game, such as MainMenuState,
 * GameState, PauseState, etc., and implements its own unique behavior for methods
 * defined in this base class.
 */
class GameStateBase
{
public:

	/**
	 * @brief Deleted default constructor to enforce initialization with a state type.
	 */	
	GameStateBase() = delete;

	/**
	 * @brief Constructs a game state with the specified type.
	 * @param stateType The type of the game state, represented by GameStateType.
	 */
	GameStateBase(GameStateType stateType);

	virtual ~GameStateBase();

	/**
	 * @brief Retrieves the type of the current game state.
	 * @return The GameStateType representing the type of this game state.
	 */
	GameStateType GetStateType() const;

	/**
	 * @brief Initializes the game state. Run once when the state is created.
	 *
	 * This method is pure virtual and must be implemented in derived classes
	 * to initialize the specific state.
	 */
	virtual void Init() = 0;

	/**
	 * @brief Updates the game state based on the elapsed time.
	 * @param deltaTime The time elapsed since the last update.
	 *
	 * Derived classes should implement this method to update the state's logic
	 * and handle any state-specific updates.
	 */
	virtual void Update(float deltaTime) = 0;

	/**
	 * @brief Draws the current game state. This will be called every game tick.
	 *
	 * Derived classes should implement this method to render the state's visuals
	 * and display relevant information to the screen.
	 */
	virtual void Draw() = 0;

	/**
	 * @brief This method will be called once the current game state is no longer active.
	 *
	 * Derived classes should implement this method to handle pausing game logic
	 * and freezing the state's update and draw processes.
	 */
	virtual void Pause() = 0;

	/**
	 * @brief This method will be called once when the current game state is actived again.
	 *
	 * Derived classes should implement this method to resume game logic and
	 * rendering after a pause state.
	 */
	virtual void Resume() = 0;

	/**
	 * @brief This method will be called once the state exit, free resource here.
	 *
	 * Derived classes should implement this method to perform cleanup and exit
	 * actions when transitioning away from the state.
	 */
	virtual void Exit() = 0;

	/**
	 * @brief Called when a key is pressed down.
	 * @param keyevent Reference to the SDL_KeyboardEvent structure containing key event information.
	 * @link SDL_KeyboardEvent Link to SDL_KeyboardEvent structure documentation.
	 */
	virtual void OnKeyDown(const SDL_KeyboardEvent& keyevent) = 0;

	/**
	 * @brief Called when a key is released.
	 * @param keyevent Reference to the SDL_KeyboardEvent structure containing key event information.
	 * @link SDL_KeyboardEvent Link to SDL_KeyboardEvent structure documentation.
	 */
	virtual void OnKeyUp(const SDL_KeyboardEvent& keyevent) = 0;

	/**
	 * @brief Called when a mouse button is pressed down.
	 * @param mouseevent Reference to the SDL_MouseButtonEvent structure containing mouse button event information.
	 * @link SDL_MouseButtonEvent Link to SDL_MouseButtonEvent structure documentation.
	 */
	virtual void OnMouseDown(const SDL_MouseButtonEvent& mouseevent) = 0;

	/**
	 * @brief Called when a mouse button is released.
	 * @param mouseevent Reference to the SDL_MouseButtonEvent structure containing mouse button event information.
	 * @link SDL_MouseButtonEvent Link to SDL_MouseButtonEvent structure documentation.
	 */
	virtual void OnMouseUp(const SDL_MouseButtonEvent& mouseevent) = 0;

	/**
	 * @brief Called when the mouse is moved.
	 * @param motionevent Reference to the SDL_MouseMotionEvent structure containing mouse motion event information.
	 * @link SDL_MouseMotionEvent Link to SDL_MouseMotionEvent structure documentation.
	 */
	virtual void OnMouseMove(const SDL_MouseMotionEvent& motionevent) = 0;

	/**
	 * @brief Called when the mouse wheel is scrolled.
	 * @param wheelevent Reference to the SDL_MouseWheelEvent structure containing mouse wheel event information.
	 * @link SDL_MouseWheelEvent Link to SDL_MouseWheelEvent structure documentation.
	 */
	virtual void OnMouseScroll(const SDL_MouseWheelEvent& wheelevent) = 0;

	/**
	* @brief Called when a controller is connected.
	*/
	virtual void OnControllerConnected() = 0;

	/**
	 * @brief Called when a controller is disconnected.
	 */
	virtual void OnControllerDisconnected() = 0;

	/**
	 * @brief Called when the left joystick of a controller is moved along the X-axis.
	 * @param joystickEvent Reference to the SDL_ControllerAxisEvent structure containing axis motion event information.
	 * @link SDL_ControllerAxisEvent Link to SDL_ControllerAxisEvent structure documentation.
	 */
	virtual void OnControllerLeftJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent) = 0;

	/**
	 * @brief Called when the left joystick of a controller is moved along the Y-axis.
	 * @param joystickEvent Reference to the SDL_ControllerAxisEvent structure containing axis motion event information.
	 * @link SDL_ControllerAxisEvent Link to SDL_ControllerAxisEvent structure documentation.
	 */
	virtual void OnControllerLeftJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent) = 0;

	/**
	 * @brief Called when the right joystick of a controller is moved along the X-axis.
	 * @param joystickEvent Reference to the SDL_ControllerAxisEvent structure containing axis motion event information.
	 * @link SDL_ControllerAxisEvent Link to SDL_ControllerAxisEvent structure documentation.
	 */
	virtual void OnControllerRightJoystickMotionX(const SDL_ControllerAxisEvent& joystickEvent) = 0;

	/**
	 * @brief Called when the right joystick of a controller is moved along the Y-axis.
	 * @param joystickEvent Reference to the SDL_ControllerAxisEvent structure containing axis motion event information.
	 * @link SDL_ControllerAxisEvent Link to SDL_ControllerAxisEvent structure documentation.
	 */
	virtual void OnControllerRightJoystickMotionY(const SDL_ControllerAxisEvent& joystickEvent) = 0;

	/**
	 * @brief Called when a controller button is pressed down.
	 * @param buttonevent Reference to the SDL_ControllerButtonEvent structure containing controller button event information.
	 * @link SDL_ControllerButtonEvent Link to SDL_ControllerButtonEvent structure documentation.
	 */
	virtual void OnControllerButtonDown(const SDL_ControllerButtonEvent& buttonEvent) = 0;

	/**
	 * @brief Called when a controller button is released.
	 * @param buttonevent Reference to the SDL_ControllerButtonEvent structure containing controller button event information.
	 * @link SDL_ControllerButtonEvent Link to SDL_ControllerButtonEvent structure documentation.
	 */
	virtual void OnControllerButtonUp(const SDL_ControllerButtonEvent& buttonEvent) = 0;

	/**
	 * @brief Called when the left trigger of a controller is moved.
	 * @param triggerEvent Reference to the SDL_ControllerAxisEvent structure containing axis motion event information.
	 * @link SDL_ControllerAxisEvent Link to SDL_ControllerAxisEvent structure documentation.
	 */
	virtual void OnLeftTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent) = 0;

	/**
	 * @brief Called when the right trigger of a controller is moved.
	 * @param triggerEvent Reference to the SDL_ControllerAxisEvent structure containing axis motion event information.
	 * @link SDL_ControllerAxisEvent Link to SDL_ControllerAxisEvent structure documentation.
	 */
	virtual void OnRightTriggerMotion(const SDL_ControllerAxisEvent& triggerEvent) = 0;


	virtual void ImGuiDraw();

protected:
	GameStateType m_GameStateType;

};