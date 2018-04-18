#pragma once

#include "MenuItem.h"
#include "UserAction.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class StateStack;
namespace sf {
	class RenderWindow;
}

class KeyBindOption : public MenuItem {
public:
	KeyBindOption();
	KeyBindOption(const wchar_t* text, sf::Vector2f position, UserAction action);

	// MenuItem virtual methods:
	virtual void select();
	virtual void unselect();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInput();
	virtual void execute();
	virtual bool isActive();
	virtual MenuItemType getType();
	
	void assignKey(sf::Keyboard::Key key); // TODO: Make private.

private:
	StateStack* mStack;
	sf::Text mText;
	sf::Text mPressKeyText;
	UserAction mAction;
	sf::Keyboard::Key mAssignedKey;
	sf::String mActionName;
	sf::String mKeyName;
	bool mActive;
};