#include "KeyBindOption.h"
#include "KeyBindings.h"
#include "../Constants.h"
#include "KeyboardManager.h"
#include "KeyBindings.h"
#include "../State/StateStack.h"
#include "AudioManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

KeyBindOption::KeyBindOption()
	: mText()
	, mPressKeyText()
	, mAction()
	, mAssignedKey()
	, mActive(false)
{
}

KeyBindOption::KeyBindOption(const wchar_t* text, sf::Vector2f position, UserAction action)
	: mActionName(text)
	, mAction(action)
	, mAssignedKey(KeyBindings::getKey(action))
	, mKeyName(KeyboardManager::getKeyName(mAssignedKey))
	, mText()
	, mPressKeyText()
	, mActive(false)
{
	mText.setFont(Constants::font);
	mText.setFillColor(sf::Color::White);
	mText.setCharacterSize(20);
	mText.setString(mActionName + ": " + mKeyName);
	mText.setPosition(position);

	mPressKeyText.setFont(Constants::font);
	mPressKeyText.setFillColor(sf::Color::Red);
	mPressKeyText.setCharacterSize(20);
	mPressKeyText.setString("Press any key");
	mPressKeyText.setPosition(sf::Vector2f(position.x + mText.getGlobalBounds().width + 20, position.y));
}

void KeyBindOption::select() {
	mText.setFillColor(sf::Color::Red);
}

void KeyBindOption::unselect() {
	mText.setFillColor(sf::Color::White);
}

void KeyBindOption::draw(sf::RenderWindow* window) {
	window->draw(mText);

	if (mActive) {
		window->draw(mPressKeyText);
	}
}

void KeyBindOption::handleInput() {
	if (!mActive)
		return;
	
	sf::Keyboard::Key pressedKey = KeyboardManager::getKey();
	if (pressedKey != sf::Keyboard::Unknown) {
		if (pressedKey == KeyBindings::getKey(ACTION_CANCEL)) {
			AudioManager::playSound(SOUND_CANCEL);
		}
		else {
			for (int i = 0; i < NUM_ACTIONS; i++) {
				if (i != (int)mAction && pressedKey == KeyBindings::getKey((UserAction)i)) {
					AudioManager::playSound(SOUND_ERROR);
					return;
				}
			}
			AudioManager::playSound(SOUND_CONFIRM);
			assignKey(pressedKey);
		}
		mActive = false;
	}
}

void KeyBindOption::execute() {
	mActive = true;
}

MenuItemType KeyBindOption::getType() {
	return ITEM_KEY_BIND_OPTION;
}

bool KeyBindOption::isActive() {
	return mActive;
}

void KeyBindOption::assignKey(sf::Keyboard::Key key) {
	mAssignedKey = key;
	KeyBindings::setKey(mAction, key);
	mKeyName = KeyboardManager::getKeyName(key);
	mText.setString(mActionName + ": " + mKeyName);
	
	// reposition "press any key" text
	sf::Vector2f textPos = mText.getPosition();
	mPressKeyText.setPosition(sf::Vector2f(textPos.x + mText.getGlobalBounds().width + 20, textPos.y));
}
