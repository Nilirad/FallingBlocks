#include "TitleScreenState.h"
#include "StateStack.h"
#include "../Constants.h"
#include "../Utilities/KeyboardManager.h"
#include "../Utilities/Localization.h"
#include <SFML/Graphics/RenderWindow.hpp>

TitleScreenState::TitleScreenState(StateStack* stack)
	: ApplicationState(stack)
	, mText()
	, mElapsedTime(sf::Time::Zero)
	, mIsTextVisible(true)
{
	mText.setFont(Constants::font);
	mText.setFillColor(sf::Color::White);
	mText.setCharacterSize(35);
	mText.setPosition(sf::Vector2f(0, 0));
	mText.setString(Localization::getString(STRING_PRESS_ANY_KEY));
}

void TitleScreenState::start() {
	KeyboardManager::lockKeys();
}

void TitleScreenState::handleInput() {
	if (KeyboardManager::getKey() != sf::Keyboard::Unknown) {
		mStack->requestPop();
		mStack->requestPush(MAIN_MENU_STATE);
	}
}

void TitleScreenState::update(sf::Time dt) {
	mElapsedTime += dt;

	mIsTextVisible = (mElapsedTime.asMilliseconds() % 1000 < 500);
}

void TitleScreenState::render(sf::RenderWindow* window) {
	drawText(window);
}

void TitleScreenState::drawText(sf::RenderWindow* window) {
	if (!mIsTextVisible)
		return;

	window->draw(mText);
}
