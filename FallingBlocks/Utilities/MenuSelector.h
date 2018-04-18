#pragma once

#include "MenuItem.h"
#include "CommandID.h"
#include "SwitchID.h"
#include "UserAction.h"
#include "../State/StateID.h"
#include <vector>

namespace sf {
	class RenderWindow;
}

class MenuSelector {
public:
	/// \brief Default constructor.
	MenuSelector();

	~MenuSelector();

	/// \brief Initializes the selector.
	void start();
	
	/// \brief handles the selection input.
	void handleInput();
	
	/// \brief Draws the menu items to the back buffer of the window.
	void draw(sf::RenderWindow* window);
	
	/// \brief Adds a menu item to the selector.
	void addMenuItem(MenuItem* item);

	void addStateChangerMenuItem(const wchar_t* text, StateID targetState, bool popsState);

	void addKeyBindMenuItem(const wchar_t* text, UserAction action);

	void addCommandMenuItem(const wchar_t* text, CommandID commandID);

	void addSwitchMenuItem(const wchar_t* text, SwitchID switchID);

	void addSpace();

	/// \brief Gets the selected menu item.
	MenuItem* getSelectedItem();

private:
	std::vector<MenuItem*> mItems; ///< The list of menu items.
	int mSelected; ///< the index of the selected menu item.
	float mPositionY;
};
