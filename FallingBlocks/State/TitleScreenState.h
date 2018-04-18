#pragma once

#include "ApplicationState.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

class StateStack;

class TitleScreenState : public ApplicationState {
public:
	TitleScreenState(StateStack* stack);

	// Virtual ApplicationState functions:
	virtual void start();
	virtual void handleInput();
	virtual void update(sf::Time dt);
	virtual void render(sf::RenderWindow* window);

private:
	void drawText(sf::RenderWindow* window);

	sf::Text mText;
	sf::Time mElapsedTime;
	bool mIsTextVisible;
};