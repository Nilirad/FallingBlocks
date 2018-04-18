#pragma once

#include "MenuItem.h"
#include "SwitchElement.h"
#include <SFML/Graphics/Text.hpp>
#include <vector>

class SwitchMenuItem : public MenuItem {
public:
	SwitchMenuItem();

	SwitchMenuItem(const wchar_t* text, sf::Vector2f position, std::vector<SwitchElement> elements);

	// MenuItem virtual methods:
	virtual void select();
	virtual void unselect();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInput();
	virtual void execute();
	virtual bool isActive();
	virtual MenuItemType getType();

private:
	void updateText();

	std::wstring mBaseString;
	sf::Text mText;
	std::vector<SwitchElement> mElements;
	int mIndex;
	bool mActive;
};