#pragma once

namespace sf {
	class RenderWindow;
}

// TODO: Check if you can remove it
enum MenuItemType {
	ITEM_STATE_CHANGER,
	ITEM_KEY_BIND_OPTION,
	ITEM_COMMAND,
	ITEM_SWITCH,
};

class MenuItem {
public:
	/// \brief Selects this menu item.
	virtual void select() = 0;

	/// \brief Unselects this menu item.
	virtual void unselect() = 0;

	/// \brief Draws the text of the menu item to the specified window.
	virtual void draw(sf::RenderWindow* window) = 0;

	virtual void handleInput() = 0;

	virtual void execute() = 0;

	virtual bool isActive() = 0;

	virtual MenuItemType getType() = 0;
};