#pragma once

#include "ApplicationState.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class PauseState : public ApplicationState {
public:
	/// \brief The constructor.
	PauseState(StateStack* stack);

	// ApplicationState virtual functions
	virtual void start();
	virtual void handleInput();
	virtual void update(sf::Time dt);
	virtual void render(sf::RenderWindow* window);

private:
	sf::Text mPauseText; ///< The showed text.

	static sf::RectangleShape sBackground;
};