#pragma once

#include "StateID.h"
#include <SFML/System/Time.hpp>

class StateStack;
namespace sf {
	class RenderWindow;
}

class ApplicationState {
public:
	/// \brief Initialize the current state.
	virtual void start() = 0;

	/// \brief Handles the input for the current state.
	virtual void handleInput() = 0;

	/// \brief Updates the current state.
	/// \param dt How much time to step the simulation.
	virtual void update(sf::Time dt) = 0;

	/// \brief Renders the current state.
	virtual void render(sf::RenderWindow* window) = 0;

protected:
	/// \brief The constructor.
	ApplicationState(StateStack* stack);
	
	StateStack* mStack; ///< The reference to the state stack;
};