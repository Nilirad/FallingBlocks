#pragma once

#include "../Utilities/Option.h"
#include "ApplicationState.h"
#include <vector>
#include <queue>

namespace sf {
	class RenderWindow;
}

class StateStack {
public:
	/// \brief Default constructor.
	StateStack();

	void requestPop();

	void requestPush(StateID state);
	
	/// \brief Pushes a state on the stack.
	void push(StateID state);

	/// \brief Pops a state from the stack.
	void pop();

	/// \brief Adds a command to the pending list.
	void addCommand(StateID command);

	/// \brief Executes the commands in the pending list.
	void processPendingList();

	/// \brief Returns true if the stack is empty, false otherwise.
	bool isEmpty();

	/// \brief Handles input of the topmost state of the stack.
	void handleInput();

	/// \brief Renders the topmost state of the stack to the specified window.
	void render(sf::RenderWindow* window);

	/// \brief Updates the topmost state of the stack.
	void update(sf::Time dt);

private:
	std::vector<ApplicationState*> mStack; ///< The state stack.
	std::queue<StateID> mPendingList; ///< The pending list.
};