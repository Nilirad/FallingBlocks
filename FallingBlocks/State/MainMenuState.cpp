#include "MainMenuState.h"
#include "../Constants.h"
#include "../Utilities/MenuStateChanger.h"
#include "../Utilities/KeyboardManager.h"
#include "../Utilities/KeyBindings.h"
#include "../Utilities/AudioManager.h"
#include "../Utilities/HighScores.h"
#include "../Utilities/Localization.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

MainMenuState::MainMenuState(StateStack* stack)
	: ApplicationState(stack)
	, mSelector()
	, mHeaderText()
	, mScoresText()
{	
	// Menu items
	mSelector.addStateChangerMenuItem(Localization::getString(STRING_PLAY), PLAYING_STATE, true);
	mSelector.addStateChangerMenuItem(Localization::getString(STRING_OPTIONS), OPTIONS_STATE, true);
	mSelector.addStateChangerMenuItem(Localization::getString(STRING_EXIT), NONE, true);
	mSelector.start();

	// TODO: use getGlobalBounds to align text properly.
	mHeaderText.setFont(Constants::font);
	mHeaderText.setFillColor(sf::Color::White);
	mHeaderText.setString("Falling Blocks");
	mHeaderText.setCharacterSize(30);
	mHeaderText.setPosition(sf::Vector2f(0, 0));

	mScoresText.setFont(Constants::font);
	mScoresText.setFillColor(sf::Color::White);
	mScoresText.setCharacterSize(20);
	mScoresText.setPosition(sf::Vector2f(50, 200));
	std::string scoresString;
	for (int i = 0; i < NUM_SCORES; i++) {
		scoresString += std::to_string(HighScores::getScore(i)) + "\n";
	}
	mScoresText.setString(scoresString);
}

/////////////////////////////////////////////////////////////////////////////////////////

void MainMenuState::start() {
}

/////////////////////////////////////////////////////////////////////////////////////////

void MainMenuState::handleInput() {
	mSelector.handleInput();
}

/////////////////////////////////////////////////////////////////////////////////////////

void MainMenuState::update(sf::Time dt) {
}

/////////////////////////////////////////////////////////////////////////////////////////

void MainMenuState::render(sf::RenderWindow* window) {
	window->draw(mHeaderText);
	window->draw(mScoresText);
	mSelector.draw(window);
}
