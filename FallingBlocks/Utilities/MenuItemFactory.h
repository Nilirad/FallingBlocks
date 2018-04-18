#pragma once

#include "UserAction.h"
#include "CommandID.h"
#include "SwitchID.h"
#include "../State/StateID.h"
#include <SFML/System/Vector2.hpp>

class MenuItem;
class StateStack;

class MenuItemFactory {
public:
	static void init(StateStack* stack);

	static MenuItem* createStateChangerMenuItem(const wchar_t* text, sf::Vector2f position,
		StateID targetState, bool popsState);

	static MenuItem* createKeyBindMenuItem(const wchar_t* text, sf::Vector2f position, UserAction action);

	static MenuItem* createCommandMenuItem(const wchar_t* text, sf::Vector2f position, CommandID command);

	static MenuItem* createSwitchMenuItem(const wchar_t* text, sf::Vector2f position, SwitchID switchID);

private:
	static StateStack* sStack;
};