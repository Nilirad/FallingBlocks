#include "PauseState.h"
#include "StateStack.h"
#include "../Utilities/KeyboardManager.h"
#include "../Utilities/KeyBindings.h"
#include "../Utilities/AudioManager.h"
#include "../Utilities/Localization.h"
#include "../Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////  STATIC DATA  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

sf::RectangleShape PauseState::sBackground = sf::RectangleShape(sf::Vector2f(PX_WINDOW_WIDTH, PX_WINDOW_HEIGHT));



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

PauseState::PauseState(StateStack * stack)
	: ApplicationState(stack)
	, mPauseText()
{
	mPauseText.setFont(Constants::font);
	mPauseText.setCharacterSize(70);
	mPauseText.setFillColor(sf::Color::White);
	mPauseText.setString(Localization::getString(STRING_PAUSE));
	float posX = PX_WINDOW_WIDTH / 2 - mPauseText.getGlobalBounds().width / 2;
	float posY = PX_WINDOW_HEIGHT / 2 - mPauseText.getGlobalBounds().height / 2;
	mPauseText.setPosition(sf::Vector2f(posX, posY));

	sBackground.setFillColor(sf::Color(0, 0, 0, 128));
}

/////////////////////////////////////////////////////////////////////////////////////////

void PauseState::start() {
	AudioManager::playSound(SOUND_CONFIRM);
}

/////////////////////////////////////////////////////////////////////////////////////////

void PauseState::handleInput() {
	if (KeyboardManager::isKeyPressedSingle(KeyBindings::getKey(ACTION_CONFIRM))) {
		AudioManager::playSound(SOUND_CONFIRM);
		mStack->requestPop();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PauseState::update(sf::Time dt) {
}

/////////////////////////////////////////////////////////////////////////////////////////

void PauseState::render(sf::RenderWindow* window) {
	window->draw(sBackground);
	window->draw(mPauseText);
}
