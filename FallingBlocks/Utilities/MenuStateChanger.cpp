#include "MenuStateChanger.h"
#include "../State/StateStack.h"
#include "../Constants.h"
#include "../Utilities/AudioManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

MenuStateChanger::MenuStateChanger()
	: mText()
	, mIsSelected(false)
	, mPopsState(true)
{
}

/////////////////////////////////////////////////////////////////////////////////////////

MenuStateChanger::MenuStateChanger(const wchar_t* text, sf::Vector2f position, StateID targetStateID, StateStack* stack, bool popsState)
	: mText()
	, mIsSelected(false)
	, mTargetState(targetStateID)
	, mPopsState(popsState)
	, mStack(stack)
{
	mText.setFont(Constants::font);
	mText.setFillColor(sf::Color::White);
	mText.setCharacterSize(20);
	mText.setString(text);
	mText.setPosition(position);
}

/////////////////////////////////////////////////////////////////////////////////////////

void MenuStateChanger::select() {
	mIsSelected = true;
	mText.setFillColor(sf::Color::Red);
}

/////////////////////////////////////////////////////////////////////////////////////////

void MenuStateChanger::unselect() {
	mIsSelected = false;
	mText.setFillColor(sf::Color::White);
}

/////////////////////////////////////////////////////////////////////////////////////////

void MenuStateChanger::draw(sf::RenderWindow* window) {
	window->draw(mText);
}

void MenuStateChanger::handleInput()
{
}

void MenuStateChanger::execute() {
	if (mPopsState) {
		mStack->requestPop();
	}
	if (mTargetState != NONE) {
		mStack->requestPush(mTargetState);
	}
}

bool MenuStateChanger::isActive() {
	return false;
}

MenuItemType MenuStateChanger::getType() {
	return ITEM_STATE_CHANGER;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool MenuStateChanger::popsState() {
	return mPopsState;
}
