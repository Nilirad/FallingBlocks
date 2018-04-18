#include "MenuItemFactory.h"
#include "MenuStateChanger.h"
#include "KeyBindOption.h"
#include "CommandMenuItem.h"
#include "SwitchMenuItem.h"

StateStack* MenuItemFactory::sStack;

void MenuItemFactory::init(StateStack* stack) {
	sStack = stack;
}

MenuItem* MenuItemFactory::createStateChangerMenuItem(
	const wchar_t* text, sf::Vector2f position, StateID targetState, bool popsState)
{
	return new MenuStateChanger(text, position, targetState, sStack, popsState);
}

MenuItem* MenuItemFactory::createKeyBindMenuItem(const wchar_t* text,
	sf::Vector2f position, UserAction action)
{
	return new KeyBindOption(text, position, action);
}

MenuItem* MenuItemFactory::createCommandMenuItem(const wchar_t* text,
	sf::Vector2f position, CommandID command)
{
	return new CommandMenuItem(text, position, command);
}

MenuItem* MenuItemFactory::createSwitchMenuItem(const wchar_t * text,
	sf::Vector2f position, SwitchID switchID)
{
	std::vector<SwitchElement> switchElements;
	if (switchID == SWITCH_LANGUAGE) {
		switchElements.push_back(SwitchElement(L"English", COMMAND_SET_ENGLISH_LANGUAGE));
		switchElements.push_back(SwitchElement(L"Italiano", COMMAND_SET_ITALIAN_LANGUAGE));
		return new SwitchMenuItem(text, position, switchElements);
	}
	return nullptr;
}
