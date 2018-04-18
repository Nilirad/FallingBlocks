#include "OptionsState.h"
#include "../Utilities/MenuStateChanger.h"
#include "../Utilities/KeyBindOption.h"
#include "../Utilities/KeyboardManager.h"
#include "../Utilities/KeyBindings.h"
#include "../Utilities/CommandMenuItem.h"
#include "../Utilities/SwitchMenuItem.h"
#include "../Utilities/AudioManager.h"
#include "../Utilities/Localization.h"
#include "../Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

OptionsState::OptionsState(StateStack* stack)
	: ApplicationState(stack)
	, mSelector()
{
	mHeaderText = sf::Text();
	mHeaderText.setFont(Constants::font);
	mHeaderText.setFillColor(sf::Color::White);
	mHeaderText.setString(Localization::getString(STRING_OPTIONS));
	mHeaderText.setCharacterSize(30);
	mHeaderText.setPosition(sf::Vector2f(0, 0));
	
	mSelector.addStateChangerMenuItem(Localization::getString(STRING_ACTION_BACK), MAIN_MENU_STATE, true);
	mSelector.addSpace();
	mSelector.addKeyBindMenuItem(Localization::getString(STRING_ACTION_UP), ACTION_MOVE_UP);
	mSelector.addKeyBindMenuItem(Localization::getString(STRING_ACTION_DOWN), ACTION_MOVE_DOWN);
	mSelector.addKeyBindMenuItem(Localization::getString(STRING_ACTION_LEFT), ACTION_MOVE_LEFT);
	mSelector.addKeyBindMenuItem(Localization::getString(STRING_ACTION_RIGHT), ACTION_MOVE_RIGHT);
	mSelector.addKeyBindMenuItem(Localization::getString(STRING_ACTION_ROTATE_LEFT), ACTION_ROTATE_LEFT);
	mSelector.addKeyBindMenuItem(Localization::getString(STRING_ACTION_ROTATE_RIGHT), ACTION_ROTATE_RIGHT);
	mSelector.addKeyBindMenuItem(Localization::getString(STRING_ACTION_HOLD), ACTION_HOLD);
	mSelector.addSpace();
	mSelector.addSwitchMenuItem(Localization::getString(STRING_ACTION_LANGUAGE), SWITCH_LANGUAGE);
	mSelector.addSpace();
	mSelector.addCommandMenuItem(Localization::getString(STRING_ACTION_SAVE), COMMAND_SAVE_OPTIONS);
	
	//mSelector.addMenuItem(new MenuStateChanger(Localization::getString(STRING_ACTION_BACK), sf::Vector2f(20, 35), MAIN_MENU_STATE, stack, true));

	//mSelector.addMenuItem(new KeyBindOption(Localization::getString(STRING_ACTION_UP), sf::Vector2f(20, 65), ACTION_MOVE_UP));
	//mSelector.addMenuItem(new KeyBindOption(Localization::getString(STRING_ACTION_DOWN), sf::Vector2f(20, 90), ACTION_MOVE_DOWN));
	//mSelector.addMenuItem(new KeyBindOption(Localization::getString(STRING_ACTION_LEFT), sf::Vector2f(20, 115), ACTION_MOVE_LEFT));
	//mSelector.addMenuItem(new KeyBindOption(Localization::getString(STRING_ACTION_RIGHT), sf::Vector2f(20, 140), ACTION_MOVE_RIGHT));
	//mSelector.addMenuItem(new KeyBindOption(Localization::getString(STRING_ACTION_ROTATE_LEFT), sf::Vector2f(20, 165), ACTION_ROTATE_LEFT));
	//mSelector.addMenuItem(new KeyBindOption(Localization::getString(STRING_ACTION_ROTATE_RIGHT), sf::Vector2f(20, 190), ACTION_ROTATE_RIGHT));
	//mSelector.addMenuItem(new KeyBindOption(Localization::getString(STRING_ACTION_HOLD), sf::Vector2f(20, 215), ACTION_HOLD));
	//
	//std::vector<SwitchElement> languageElements;
	//languageElements.push_back(SwitchElement(L"English", new SetEnglishLanguageCommand()));
	//languageElements.push_back(SwitchElement(L"Italiano", new SetItalianLanguageCommand()));
	//mSelector.addMenuItem(new SwitchMenuItem(Localization::getString(STRING_ACTION_LANGUAGE), sf::Vector2f(20, 245), languageElements));

	////TODO: Do for commands the same enum + factory stuff you made with states.
	//mSelector.addMenuItem(new CommandMenuItem(Localization::getString(STRING_ACTION_SAVE), sf::Vector2f(20, 275), new SaveOptionsCommand()));

	mSelector.start();
}

/////////////////////////////////////////////////////////////////////////////////////////

void OptionsState::start() {
}

/////////////////////////////////////////////////////////////////////////////////////////

void OptionsState::handleInput() {
	mSelector.handleInput();
}

/////////////////////////////////////////////////////////////////////////////////////////

void OptionsState::update(sf::Time dt) {
}

/////////////////////////////////////////////////////////////////////////////////////////

void OptionsState::render(sf::RenderWindow* window) {
	window->draw(mHeaderText);
	mSelector.draw(window);
}
