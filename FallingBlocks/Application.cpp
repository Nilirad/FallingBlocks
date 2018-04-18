#include "Application.h"
#include "Constants.h"
#include "State/StateFactory.h"
#include "Utilities/KeyboardManager.h"
#include "Utilities/KeyBindings.h"
#include "Utilities/AudioManager.h"
#include "Utilities/HighScores.h"
#include "Utilities/Localization.h"
#include "Utilities/MenuItemFactory.h"
#include <SFML/Window/Event.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////  METHODS  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

Application::Application(int anything)
	: mWindow(sf::VideoMode(PX_WINDOW_WIDTH, PX_WINDOW_HEIGHT), "Falling Blocks")
	, mStack()
{
	Constants::init();
	KeyboardManager::init();
	KeyBindings::init();
	AudioManager::init();
	StateFactory::init(&mStack);
	HighScores::init();
	Localization::init();
	MenuItemFactory::init(&mStack);
}

/////////////////////////////////////////////////////////////////////////////////////////

void Application::run() {
	mStack.requestPush(TITLE_SCREEN_STATE);
	mStack.processPendingList();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen() && !mStack.isEmpty()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > FRAME_TIME) {
			timeSinceLastUpdate -= FRAME_TIME;
			processEvents();
			handleInput();
			update(FRAME_TIME);
			mStack.processPendingList();
		}
		render();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void Application::processEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			mWindow.close();
			break;
		default:
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void Application::handleInput() {
	KeyboardManager::checkKeyPresses();
	mStack.handleInput();
}

/////////////////////////////////////////////////////////////////////////////////////////

void Application::render() {
	mWindow.clear();

	mStack.render(&mWindow);

	mWindow.display();
}

/////////////////////////////////////////////////////////////////////////////////////////

void Application::update(sf::Time dt) {
	mStack.update(dt);
}