#pragma once

#include "ApplicationState.h"
#include "../Utilities/MenuSelector.h"
#include <SFML/Graphics/Text.hpp>

class OptionsState : public ApplicationState {
public:
	/// \brief The constructor.
	OptionsState(StateStack* stack);

	// virtual methods
	virtual void start();
	virtual void handleInput();
	virtual void update(sf::Time dt);
	virtual void render(sf::RenderWindow* window);

private:
	MenuSelector mSelector; ///< The menu's item selector.
	sf::Text mHeaderText; ///< The menu text.
	bool mJustChangedState;
};
