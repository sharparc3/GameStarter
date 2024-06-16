#pragma once
#include <stack>
#include <memory>
#include "SingletonDclp.h"
#include "Config.h"
#include "GameStateBase.h"

class GameStateBase;

/**
 * @brief Manages the game state transitions and maintains the state stack.
 *
 * The GameStateMachine class is responsible for initializing, cleaning up,
 * and managing the game states in a stack-like manner. It allows pushing and
 * popping states, get the current state, and checking the running status
 * of the game.
 */
class GameStateMachine final : public SingletonDclp<GameStateMachine>
{
public:
	/**
	 * @brief Initializes the game state machine.
	 *
	 * This method sets up the necessary components for the state machine to operate
	 * and push an initial state into the stack
	 */
	void Init();

	/**
	 * @brief Cleans up the game state machine.
	 *
	 * This method performs cleanup tasks, ensuring all resources are properly released.
	 */
	void CleanUp();

	/**
	 * @brief Pushes a new game state onto the state stack.
	 * @param stateType The type of the game state to push onto the stack.
	 *
	 * This method creates a new game state of the specified type and 
	 * mark it as the next state to be pushed into stack.
	 */
	void PushState(GameStateType stateType);

	/**
	 * @brief Pops the current game state off the state stack.
	 *
	 * This method removes the current game state from the stack and resumes the previous
	 * state, if any.
	 */
	void PopState();

	/**
	 * @brief Update the state machine.
	 *
	 * This method perform state changing task: push, pop new state into stack
	 */
	void Update();

	/**
	 * @brief Exits the game state machine.
	 *
	 * This method signals the game state machine to exit, 
	 * pops all states from the stack
	 */
	void Exit();

	/**
	 * @brief Checks if the state machine has any active states.
	 * @return True if there is at least one active state, false otherwise.
	 */
	bool HasState();

	/**
	 * @brief Gets the current active game state.
	 * @return A shared pointer to the current active game state.
	 *
	 * This method returns a shared pointer to the current game state on top of the stack.
	 */
	std::shared_ptr<GameStateBase> GetCurrentState();

	/**
	 * @brief Checks if the game state machine is running.
	 * @return True if the game state machine is running, false if it has been signaled to exit.
	 *
	 * This inline method returns the running status of the game state machine.
	 */
	inline bool IsRunning() const { return !m_exit; };

private:
	/**
	 * @brief Stack of game states managed by the state machine.
	 *
	 * This stack contains shared pointers to the active game states, allowing
	 * for easy state transitions and management. The top of the stack is the
	 * current active state.
	 */
	std::stack<std::shared_ptr<GameStateBase>> m_stateStack;

	/**
	 * @brief Pointer to the current active game state.
	 *
	 * This shared pointer holds the current active game state, providing direct
	 * access to the state at the top of the stack for updates, event handling and rendering...
	 */
	std::shared_ptr<GameStateBase> m_pActiveState;

	/**
	 * @brief Pointer to the next game state to be pushed onto the stack.
	 *
	 * This shared pointer indicates the next game state to be activated. If it is
	 * not null, the state machine will push this state onto the stack in the next
	 * game tick.
	 */
	std::shared_ptr<GameStateBase> m_pNextState;

	/**
	 * @brief Flag indicating if the game loop should exit.
	 *
	 * This boolean flag controls the game loop's execution. If set to true, the game
	 * loop will stop, and the program will terminate.
	 */
	bool m_exit;

};

/**
 * @brief Creates a game state of the specified type.
 * @param gameStateType The type of game state to create.
 * @return A shared pointer to the newly created game state.
 *
 * This method is responsible for creating instances of game states based on the
 * specified type.
 */
std::shared_ptr<GameStateBase> CreateGameState(GameStateType gameStateType);