#pragma once

#include "MenuItem.h"
#include "Command.h"
#include <SFML/Graphics/Text.hpp>

class CommandMenuItem : public MenuItem {
public:
	CommandMenuItem();

	CommandMenuItem(const wchar_t* text, sf::Vector2f position, CommandID command);

	// virtual MenuItem functions.
	virtual void select();
	virtual void unselect();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInput();
	virtual void execute();
	virtual bool isActive();
	virtual MenuItemType getType();

private:
	sf::Text mText;
	CommandID mCommand;
};