#include "SwitchMenuItem.h"
#include "KeyboardManager.h"
#include "KeyBindings.h"
#include "../Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

SwitchMenuItem::SwitchMenuItem()
	: mBaseString()
	, mText()
	, mElements()
	, mIndex(0)
	, mActive(false)
{
}

SwitchMenuItem::SwitchMenuItem(const wchar_t* text, sf::Vector2f position, std::vector<SwitchElement> elements)
	: mBaseString(text)
	, mText()
	, mElements(elements)
	, mIndex(0)
	, mActive(false)
{
	updateText();
	mText.setFont(Constants::font);
	mText.setCharacterSize(20);
	mText.setFillColor(sf::Color::White);
	mText.setPosition(position);
}

void SwitchMenuItem::select() {
	mText.setFillColor(sf::Color::Red);
	mActive = true;
}

void SwitchMenuItem::unselect() {
	mText.setFillColor(sf::Color::White);
	mActive = false;
}

void SwitchMenuItem::draw(sf::RenderWindow * window) {
	window->draw(mText);
}

void SwitchMenuItem::handleInput() {
	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_MOVE_LEFT))) {
		mIndex -= 1;
		if (mIndex < 0) {
			mIndex = mElements.size() - 1;
		}
		mElements[mIndex].execute();
		updateText();
	}
	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_MOVE_RIGHT))) {
		mIndex += 1;
		if (mIndex == mElements.size()) {
			mIndex = 0;
		}
		mElements[mIndex].execute();
		updateText();
	}

	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_MOVE_UP))
		|| KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_MOVE_DOWN)))
	{
		mActive = false;
	}
}

void SwitchMenuItem::execute() {
}

bool SwitchMenuItem::isActive()
{
	return mActive;
}

MenuItemType SwitchMenuItem::getType()
{
	return ITEM_SWITCH;
}

void SwitchMenuItem::updateText() {
	mText.setString(mBaseString + L" " + mElements[mIndex].getText());
}
