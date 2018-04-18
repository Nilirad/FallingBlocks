#pragma once

#include "State/StateStack.h"
#include <SFML/Graphics/RenderWindow.hpp>

const sf::Time FRAME_TIME = sf::seconds(1.f / 60.f); ///< The duration of a frame.

class Application {
public:
	/// \brief The default constructor.
	/// \param anything A value needed for compiler reasons. Any value is good.
	Application(int anything);
	
	/// \brief Runs the current application.
	void run();

private:
	sf::RenderWindow mWindow; ///< The window to render on.
	StateStack mStack; ///< The state stack.

	/// \brief Process the events raised by the window.
	void processEvents();

	/// \brief Handles the input.
	void handleInput();

	/// \brief Renders the current state.
	void render();

	/// \brief Updates the application.
	void update(sf::Time dt);
};