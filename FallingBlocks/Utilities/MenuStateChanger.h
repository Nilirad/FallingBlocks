#pragma once

#include "MenuItem.h"
#include "../State/ApplicationState.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf {
	class RenderWindow;
}

class MenuStateChanger : public MenuItem {
public:
	/// \brief Default constructor.
	MenuStateChanger();

	/// \brief Constructor.
	MenuStateChanger(const wchar_t* text, sf::Vector2f position, StateID targetStateID, StateStack* stack, bool popsState);

	// MenuItem virtual methods:
	virtual void select();
	virtual void unselect();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInput();
	virtual void execute();
	virtual bool isActive();
	virtual MenuItemType getType();

	/// \brief True if pops a state when executed.
	bool popsState();

private:
	sf::Text mText; ///< The text to be displayed.
	// TODO: Useless attribute?
	bool mIsSelected; ///< States if it is selected.
	bool mPopsState; ///< States if it pops the state when executed.
	StateID mTargetState; ///< The ID of the state to be triggered when executed.
	StateStack* mStack; ///< The reference to the state stack.
};